#ifndef SERVERSOCKETTPC_H_
#define SERVERSOCKETTPC_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>

#include "../Functions.h"
#include "../InitializationException.h"
#include "../IllegalParameterException.h"

#ifdef USE_LOGGER
#include "../logger/Logger.h"
#endif

#include "NetworkException.h"

#include "SocketTCP.h"

namespace cpputil {
namespace network {

class ServerSocketTCP
#ifdef USE_LOGGER
: public cpputil::logger::Loggable
#endif
  {
public:
	ServerSocketTCP(unsigned short port);

	virtual ~ServerSocketTCP();

	void bindPort();
	void startListen();
	void startListen(unsigned int max);
	SocketTCP* acceptConnection();
	void releasePort();

protected:
	unsigned short portNumber;

private:
	int serverSocket;
	sockaddr_in serverAddress;
	bool isBinded;
#ifdef USE_LOGGER
	cpputil::logger::Logger* logger;
#endif

};

}
}

#endif /*SERVERSOCKETTPC_H_*/
