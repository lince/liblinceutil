#ifndef CLIENTSOCKETTCP_H_
#define CLIENTSOCKETTCP_H_

//#define USE_LOGGER

#include <sys/socket.h>
#include <arpa/inet.h>
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


namespace cpputil {
namespace network {

class DataPayload {
public:
	DataPayload(const int lenght, unsigned char* data, bool copy=false);
	DataPayload(std::string str);
	~DataPayload();

	int getLenght();
	unsigned char* getData();
	std::string getDataAsString();

private:
	int lenght;
	unsigned char* data;

friend class SocketTCP;
};

class ServerSocketTCP;

class SocketTCP
#ifdef USE_LOGGER
: public cpputil::logger::Loggable
#endif
  {

public:
	SocketTCP(std::string ip, unsigned short port);
	void connectSocket();
	DataPayload* receiveData();
	int sendData(DataPayload* data);
	void closeConnection();

	std::string getIPAddress();
	unsigned short getPortNumber();

protected:
	SocketTCP(int clientSocket, sockaddr_in clientAddres);

private:
	int _socket;
	std::string ipAddress;
	unsigned short portNumber;
	sockaddr_in addres;
	bool isConnected;

#ifdef USE_LOGGER
	cpputil::logger::Logger* logger;
#endif

friend class ServerSocketTCP;
};

}
}

#endif /*CLIENTSOCKETTCP_H_*/
