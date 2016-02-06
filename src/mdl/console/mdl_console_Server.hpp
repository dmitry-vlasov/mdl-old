/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_console_Server.hpp                                   */
/* Description:     mdl server for remote control                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace mdl {
namespace console {

class Server :
	public object :: Object,
	public Scalar<Server> {
public :
	Server (Engine* engine);
	virtual ~ Server();

	void run();
	String& outputBuffer();
	String& messageBuffer();
	int getConnection() const;
	static Server* get();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_COMMAND_VECTOR_CAPACITY = 32,
		INITIAL_BUFFER_CAPACITY  = 4096
	};
	typedef
		vector :: Vector
		<
			Command,
			storage :: ByPointer,
			allocator :: Heap
		>
		CommandVector_;

	bool start();
	bool receiveCommand();
	bool executeCommand();
	bool sendData();
	bool sendMessages();
	bool closeConnection();
	bool stop();

	static Server* server_;

	Engine*        engine_;
	CommandVector_ commandVector_;
	String         outputBuffer_;
	String         messageBuffer_;
	char           inputBuffer_ [INITIAL_BUFFER_CAPACITY];

	sockaddr_in serverAddress_;
	sockaddr_in clientAddress_;
	socklen_t   clientLength_;

	int socket_;
	int connection_;
	int port_;

	bool exit_;
};

}
}


