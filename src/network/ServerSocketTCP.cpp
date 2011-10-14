#include "../../include/network/ServerSocketTCP.h"

#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
using namespace std;

#define MAX_BACKLOG	128

namespace cpputil {
namespace network {

ServerSocketTCP::ServerSocketTCP(unsigned short port) {
#ifdef USE_LOGGER
	logger = cpputil::logger::Logger::getInstance();
	logger->registerClass(this, "cpputil::network::ServerSocketTCP");

	TRACE(logger, "Construtor");
#endif

	this->portNumber = port;

	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket < 0) {
		string errMsg = strerror(errno);
		throw NetworkException(
				"Server Socket couldn't be created: " + errMsg,
				"cpputil::network::ServerSocketTCP",
				"ServerSocket(unsigned short");
	}

	memset((void*)& serverAddress, 0, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	isBinded = false;
}

ServerSocketTCP::~ServerSocketTCP() {
#ifdef USE_LOGGER
	TRACE(logger, "Destrutor");
#endif

	close(serverSocket);
}

void ServerSocketTCP::bindPort() {
#ifdef USE_LOGGER
	TRACE(logger, "bindPort()");
#endif

	if (bind(serverSocket, (struct sockaddr *) &serverAddress,
			sizeof(serverAddress)) < 0) {

		string errMsg = strerror(errno);
		throw NetworkException(
				"Couldn't realize the binding: " + errMsg,
				"cpputil::network::ServerSocketTCP",
				"bindPort()");
	}
	isBinded = true;
}

void ServerSocketTCP::startListen() {
#ifdef USE_LOGGER
	TRACE(logger, "startListen()");
#endif

	if (listen(serverSocket, MAX_BACKLOG) < 0) {
		string errMsg = strerror(errno);
		throw NetworkException(
				"Error while listening for connections: " + errMsg,
				"cpputil::network::ServerSocketTCP",
				"startListen()");
	}
}

void ServerSocketTCP::startListen(unsigned int max) {
#ifdef USE_LOGGER
	TRACE(logger, "startListen(unsigned int max)");
#endif

	if (max > 128) {
		throw IllegalParameterException(
				"Tried a backlog number bigger than the maximum allowed (128).",
				"cpputil::network::ServerSocketTCP",
				"startListen(unsigned int)");
	}
	if (listen(serverSocket, MAX_BACKLOG) < 0) {
		string errMsg = strerror(errno);
		throw NetworkException(
				"Error while listening for connections: " + errMsg,
				"cpputil::network::ServerSocketTCP",
				"startListen(unsigned int)");
	}
}

SocketTCP* ServerSocketTCP::acceptConnection() {
#ifdef USE_LOGGER
	TRACE(logger, "acceptConnection()");
#endif

	sockaddr_in clientAddres;
	int size = sizeof(clientAddres);
	int client = accept(serverSocket,
			(struct sockaddr *) &clientAddres, (socklen_t*) &size);

	if (client < 0) {
		string errMsg = strerror(errno);
		throw NetworkException(
				"Error trying to accept connections: " + errMsg,
				"cpputil::network::ServerSocketTCP",
				"acceptConnection()");
	}

	return new SocketTCP(client, clientAddres);
}

void ServerSocketTCP::releasePort() {
#ifdef USE_LOGGER
	TRACE(logger, "releasePort()");
#endif

	if (!isBinded) {
		throw InitializationException(
						"Try to release port, but port hasn't binded yet.",
						"cpputil::network::ServerSocketTCP",
						"releasePort()");
	}

	if (shutdown(serverSocket, SHUT_RDWR) < 0) {
		string errMsg = strerror(errno);
		throw NetworkException(
				"Error trying to release the port: " + errMsg,
				"cpputil::network::ServerSocketTCP",
				"releasePort()");
	}
}

}
}
