/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_console_Server.cpp                                   */
/* Description:     mdl server for remote control                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cerrno>
#include <cstring>

extern int errno;

namespace mdl {
namespace console {

using namespace exception;

	/****************************
	 *		Public members
	 ****************************/

	Server :: Server (Engine* engine) :
	engine_(engine),
	commandVector_ (INITIAL_COMMAND_VECTOR_CAPACITY),
	outputBuffer_ (INITIAL_BUFFER_CAPACITY),
	messageBuffer_ (INITIAL_BUFFER_CAPACITY),
	inputBuffer_ (),
	serverAddress_ (),
	clientAddress_ (),
	clientLength_ (),
	socket_ (-1),
	connection_ (-1),
	port_ (Config :: serverPort()),
	exit_ (false)
	{
		if (server_ != NULL) {
			Error* error = new Error(Error :: SEMANTIC, "double instance of server");
			throw error;
		}
		server_ = this;
	}
	Server :: ~ Server()
	{
		stop();
		server_ = NULL;
	}

using std :: endl;
using std :: cout;

	void
	Server :: run()
	{
		if (!start()) {
			return;
		}
		while (!exit_) {
			Timer timer;
			timer.start();
			try {
				bool success = true;
				success = success && start();
				success = success && receiveCommand();
				success = success && executeCommand();
				success = success && sendData();
				success = success && sendMessages();
				success = success && closeConnection();
			} catch (Error* error) {
				std :: cerr << *error << std :: endl;
				engine_->clear();
			} catch (std :: exception& e) {
				std :: cerr << e.what() << std :: endl;
				engine_->clear();
			} catch (...) {
				std :: cerr << "<unknown exception>" << std :: endl;
				engine_->clear();
			}
			timer.stop();
			std :: cout << "done." << std :: endl;
		}
		stop();
		showInfo (std :: cout);
	}
	inline String&
	Server :: outputBuffer() {
		return outputBuffer_;
	}
	inline String&
	Server :: messageBuffer() {
		return messageBuffer_;
	}
	inline int
	Server :: getConnection() const {
		return connection_;
	}
	inline Server*
	Server :: get() {
		return server_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Server :: commitSuicide() {
		delete this;
	}
	Size_t
	Server :: getVolume() const
	{
		Size_t volume = 0;
		volume += commandVector_.getVolume();
		volume += outputBuffer_.getVolume();
		volume += messageBuffer_.getVolume();
		volume += getSizeOf();
		return volume;
	}
	Size_t
	Server :: getSizeOf() const {
		return sizeof (Server);
	}
	void
	Server :: show (String& string) const
	{
		for (int i = 0; i < commandVector_.getSize(); ++ i) {
			const Command* command = commandVector_.getValue(i);
			string << *command << endLine;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Server :: start()
	{
		if (socket_ >= 0) {
			return true;
		}
		socket_ = socket (AF_INET, SOCK_STREAM, 0);
		if (socket_ < 0) {
			std :: cerr << "error opening socket (errno: " << errno << ")" << std :: endl;
			std :: cerr << "--------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		}
		bzero ((char *) &serverAddress_, sizeof (serverAddress_));
		serverAddress_.sin_family      = AF_INET;
		serverAddress_.sin_addr.s_addr = INADDR_ANY;
		serverAddress_.sin_port        = htons (port_);
		if (bind (socket_, (struct sockaddr *) &serverAddress_, sizeof (serverAddress_)) < 0) {
			std :: cerr << "error on mdl server binding with port " << port_ << " ";
			std :: cerr << "(errno: " << errno << ")" << std :: endl;
			std :: cerr << "------------------------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		} else {
			std :: cout << "mdl server started" << std :: endl;
			std :: cout << "------------------" << std :: endl;
			return true;
		}
	}
	bool
	Server :: receiveCommand()
	{
		inputBuffer_ [INITIAL_BUFFER_CAPACITY - 1] = '\0';
		if (listen (socket_, 10)) {
			std :: cerr << "error on listen (errno: " << errno << ")" << std :: endl;
			std :: cerr << "--------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		}
		clientLength_ = sizeof (clientAddress_);
		connection_ = accept (socket_, (struct sockaddr *) &clientAddress_, &clientLength_);
		if (connection_ < 0) {
			std :: cerr << "error on accept (errno: " << errno << ")" << std :: endl;
			std :: cerr << "--------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		}
		bzero (inputBuffer_, INITIAL_BUFFER_CAPACITY);
		int n = read (connection_, inputBuffer_, INITIAL_BUFFER_CAPACITY - 1);
		if (n < 0) {
			std :: cerr << "error reading from socket (errno: " << errno << ")" << std :: endl;
			std :: cerr << "--------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		}
		return true;
	}
	bool
	Server :: executeCommand()
	{
		Command* command = new Command (inputBuffer_);
		commandVector_.add (command);
		command->parse (engine_);
		std :: cout << "executing \"" << *command << "\" ... " << std :: flush;
		outputBuffer_.clear();
		messageBuffer_.clear();
		if (command->getId() == Command :: EXIT) {
			exit_ = true;
			outputBuffer_ << "<exit/>" << endLine;
		} else if (command->isSane()) {
			command->execute (engine_);
		} else {
			std :: cout << "command " << inputBuffer_ << " is incorrect." << std :: endl;
			std :: cout << "run 'help' to see the command list." << std :: endl;
			messageBuffer_ << "command " << inputBuffer_ << " is incorrect." << endLine;
			messageBuffer_ << "run 'help' to see the command list." << endLine;
		}
		return true;
	}
	bool
	Server :: sendData()
	{
		if (outputBuffer_.getSize() > 0) {
			std :: cout << "to write data: " << outputBuffer_.getSize() << " bytes. ";
		}
		int bytesWritten = write (connection_, outputBuffer_.c_str(), outputBuffer_.getSize());
		if (bytesWritten < 0) {
			std :: cerr << "write failed (errno: " << errno << ")" << std :: endl;
			std :: cerr << "--------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		} else if (bytesWritten > 0) {
			std :: cout << bytesWritten << " data bytes are written. ";
		}
		return true;
	}
	bool
	Server :: sendMessages()
	{
		if (messageBuffer_.getSize() > 0) {
			std :: cout << "to write message: " << messageBuffer_.getSize() << " bytes. ";
		}
		// Write a delimiter between data and messages: null char
		int bytesWritten = write (connection_, "\0", 1);
		if (bytesWritten < 0) {
			std :: cerr << "write failed (errno: " << errno << ")" << std :: endl;
			std :: cerr << "--------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		}
		// Write messages
		bytesWritten = write (connection_, messageBuffer_.c_str(), messageBuffer_.getSize());
		if (bytesWritten < 0) {
			std :: cerr << "write failed (errno: " << errno << ")" << std :: endl;
			std :: cerr << "--------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		} else if (bytesWritten > 0) {
			std :: cout << bytesWritten << " message bytes are written. ";
		}
		return true;
	}
	bool
	Server :: closeConnection()
	{
		if (close (connection_) < 0) {
			std :: cerr << "error on close (errno: " << errno << ")" << std :: endl;
			std :: cerr << "--------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		} else {
			return true;
		}
	}
	bool
	Server :: stop()
	{
		if (socket_ < 0) {
			return true;
		}
		std :: cout << "mdl server is stopping ... ";
		if (close (socket_) < 0) {
			std :: cerr << "error on closing socket (errno: " << errno << ")" << std :: endl;
			std :: cerr << "--------------------------------" << std :: endl;
			std :: cerr << "\t" << strerror(errno) << std :: endl;
			return false;
		}
		socket_ = -1;
		std :: cout << "done." << std :: endl;
		std :: cout << "------------------" << std :: endl;
		std :: cout << "mdl server stopped" << std :: endl;
		return true;
	}

	/********************************
	 *		Private static members
	 ********************************/

	Server* Server :: server_ = NULL;
}
}


