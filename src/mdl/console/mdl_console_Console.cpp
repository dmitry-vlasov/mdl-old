/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_console_Console.cpp                                  */
/* Description:     mdl console for manual control                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <iostream>

namespace mdl {
namespace console {

using namespace exception;

	/****************************
	 *		Public members
	 ****************************/

	Console :: Console (Engine* engine) :
	engine_ (engine),
	commandVector_ (INITIAL_COMMAND_VECTOR_CAPACITY),
	outputBuffer_ (INITIAL_BUFFER_CAPACITY),
	exit_ (false)
	{
		if (console_ != NULL) {
			Error* error = new Error(Error :: SEMANTIC, "double instance of console");
			throw error;
		}
		console_ = this;
	}
	Console :: ~ Console()
	{
		if (console_ == this) {
			console_ = NULL;
		}
	}

using std :: endl;
using std :: cout;

	void
	Console :: run()
	{
		enum {
			INPUT_BUFFER_CAPACITY = 2048
		};
		std :: cout << "Welcome to mdl console" << std :: endl;
		std :: cout << "----------------------" << std :: endl;
		while (!exit_) {
			std :: cout << "> " << std :: flush;
			char buffer [INPUT_BUFFER_CAPACITY];
			std :: cin.getline (buffer, INPUT_BUFFER_CAPACITY, chars :: NEW_LINE);
			Command* command = new Command (buffer);
			commandVector_.add (command);
			command->parse (engine_);
			if (command->isSane()) {
				try {
					command->execute (engine_);
				} catch (Error* error) {
					exit_ = true;
					std :: cout << *error << std :: endl;
				} catch (std :: exception& e) {
					exit_ = true;
					std :: cout << e.what() << std :: endl;
				} catch (...) {
					exit_ = true;
					std :: cout << "<unknown exception>" << std :: endl;
				}
			}
			if (!outputBuffer_.isEmpty()) {
				std :: cout << outputBuffer_ << std :: endl;
				outputBuffer_.clear();
			}
			std :: cout << std :: flush;
			if (command->getId() == Command :: EXIT) {
				exit_ = true;
			}
		}
		showInfo (std :: cout);
	}
	inline String&
	Console :: outputBuffer() {
		return outputBuffer_;
	}
	inline Console*
	Console :: get() {
		return console_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Console :: commitSuicide() {
		delete this;
	}
	Size_t
	Console :: getVolume() const
	{
		Size_t volume = 0;
		volume += commandVector_.getVolume();
		volume += outputBuffer_.getVolume();
		volume += getSizeOf();
		return volume;
	}
	Size_t
	Console :: getSizeOf() const {
		return sizeof (Console);
	}
	void
	Console :: show (String& string) const
	{
		for (int i = 0; i < commandVector_.getSize(); ++ i) {
			const Command* command = commandVector_.getValue(i);
			string << *command << endLine;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	/********************************
	 *		Private static members
	 ********************************/

	Console* Console :: console_ = NULL;
}
}


