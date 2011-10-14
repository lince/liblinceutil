/*
 * LoggerNetworkStream.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: caioviel
 */

#include "../../include/logger/LoggerNetworkStream.h"
#include "../../include/NotImplementedException.h"

#include <iostream>
using namespace std;
using namespace cpputil::network;

namespace cpputil {
namespace logger {

LoggerNetworkStream::LoggerNetworkStream(
		Protocol protocol,
		string ipAddres,
		unsigned short  portNumber,
		Logger::LoggerLvl loggerLvl) : Logger(loggerLvl) {

	if (protocol == LoggerNetworkStream::UDP) {
		throw NotImplementedException(
				"Not Implemented Yet! Please, use another Logger Style or use TCP.",
				"cpputil::logger::LoggerNetworkStream",
				"internalMessage(string, LoggerLvl");

	}
	this->protocol = protocol;
	this->idAddres = ipAddres;
	this->portNumber = portNumber;

	socketTCP = NULL;
	connectToLoggerServer();
}

LoggerNetworkStream::~LoggerNetworkStream() {
	if (socketTCP != NULL) {
		socketTCP->closeConnection();
		delete socketTCP;
	}

}

void LoggerNetworkStream::connectToLoggerServer() {
	try {
		socketTCP = new SocketTCP(idAddres, portNumber);
		socketTCP->connectSocket();
	} catch (NetworkException& ex) {
		cerr << "Network Exception catched at"
				" LoggerNetworkStream::internalMessage(string, LoggerLvl)" << endl
				<< ex.what() << endl;
	}
}

void LoggerNetworkStream::internalMessage(string completeMessage,  Logger::LoggerLvl lvl) {
	DataPayload* data = new DataPayload(completeMessage);
	try {
		socketTCP->sendData(data);
	} catch (NetworkException& ex) {
		cerr << "Network Exception catched at"
				" LoggerNetworkStream::internalMessage(string, LoggerLvl)" << endl
				<< ex.what() << endl;
	}
	delete data;
}

} /* namespace logger */
}



 /* namespace cpputil */
