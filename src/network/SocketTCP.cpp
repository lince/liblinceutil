#include "../../include/network/SocketTCP.h"

#include <errno.h>
#include <cstring>
using namespace std;

#define MAX_BUFFERSIZE  10240

namespace cpputil {
namespace network {


DataPayload::DataPayload(const int lenght, unsigned char* _data, bool copy) {
	this->lenght = lenght;
	if (copy) {
		data = new unsigned char[this->lenght];
		memcpy(data, _data, lenght);
	} else {
		data = _data;
	}
}

DataPayload::DataPayload(std::string str) {
	lenght = str.length();
	data = new unsigned char[lenght];
	memcpy(data, str.c_str(), lenght);
}

int DataPayload::getLenght() {
	return lenght;
}

unsigned char* DataPayload::getData() {
	return data;
}

std::string DataPayload::getDataAsString() {
	data[lenght] = '\0';
	//data[lenght] = '/0';
	//data[lenght+1] = '/0';
	string s((char*) data);
	return s;
}


DataPayload::~DataPayload() {
	if (data) {
		delete data;
	}
}

SocketTCP::SocketTCP(string ip, unsigned short port) {
#ifdef USE_LOGGER
	logger = cpputil::logger::Logger::getInstance();
	logger->registerClass(this, "cpputil::network::SocketTCP");

	TRACE(logger, "Construtor Normal");
#endif

	this->portNumber = port;
	if (Functions::isIPv4(ip.c_str())) {
		this->ipAddress = ip;
	} else {
		throw IllegalParameterException(
				"'" + ip + "' is not a valid IPv4 address.",
				"cpputil::network::SocketTCP",
				"SocketTCP(string, unsigned short");
	}
	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket < 0) {
		string errMsg = strerror(errno);
		throw NetworkException(
				"Socket couldn't be created: " + errMsg,
				"cpputil::network::SocketTCP",
				"SocketTCP(string, unsigned short");
	}

	memset(&addres, 0, sizeof(addres));

	addres.sin_family = AF_INET;
	addres.sin_port = htons(port);
	inet_aton(ip.c_str(), &(addres.sin_addr));
	isConnected = false;
}

SocketTCP::SocketTCP(int clientSocket, sockaddr_in clientAddres) {
#ifdef USE_LOGGER
	logger = cpputil::logger::Logger::getInstance();
	logger->registerClass(this, "cpputil::network::SocketTCP");

	TRACE(logger, "Construtor Friend");
#endif

	this->_socket = clientSocket;
	this->portNumber = ntohs(clientAddres.sin_port);
	in_addr inAddr = clientAddres.sin_addr;
	char* buffer = inet_ntoa(inAddr);
	ipAddress = buffer;
	isConnected = true;
}

void SocketTCP::connectSocket() {
#ifdef USE_LOGGER
	TRACE(logger, "connectSocket()");
#endif

	if (isConnected) {
		throw InitializationException(
				"Socket is already connected.",
				"cpputil::network::SocketTCP",
				"connectSocket()");
	}
	int ret = connect(_socket, (struct sockaddr *) &addres, sizeof(addres));
	if (ret < 0) {
		string errMsg = strerror(errno);
		throw NetworkException(
				"Couldn't connect: " + errMsg,
				"cpputil::network::SocketTCP",
				"connectSocket()");
	}
	isConnected = true;
}

DataPayload* SocketTCP::receiveData() {
#ifdef USE_LOGGER
	TRACE(logger, "reciveData()");
#endif

	static unsigned char* buffer = new unsigned char[MAX_BUFFERSIZE];
	int bytes = recv(_socket, buffer, MAX_BUFFERSIZE-1, 0);
	if (bytes <= 0) {
		string errMsg = strerror(errno);
		throw NetworkException(
				"Error while receiving data: " + errMsg,
				"cpputil::network::SocketTCP",
				"receiveData()");
	}
	DataPayload* datap = new DataPayload(bytes, buffer, true);
	return datap;
}

int SocketTCP::sendData(DataPayload* data) {
#ifdef USE_LOGGER
	TRACE(logger, "sendData()");
#endif

	int bytes = send(_socket, data->data, data->lenght, 0);
	if (bytes < 0) {
		if (bytes < 0) {
			string errMsg = strerror(errno);
			throw NetworkException(
					"Error while sending data: " + errMsg,
					"cpputil::network::SocketTCP",
					"sendData(DataPayload* )");
		}
	}
	return bytes;
}

string SocketTCP::getIPAddress() {
	return this->ipAddress;
}

unsigned short SocketTCP::getPortNumber() {
	return this->portNumber;
}

void SocketTCP::closeConnection() {
	close(_socket);
}

}
}
