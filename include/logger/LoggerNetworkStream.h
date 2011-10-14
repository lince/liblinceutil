/*
 * LoggerNetworkStream.h
 *
 *  Created on: Jul 21, 2011
 *      Author: caioviel
 */

#ifndef LOGGERNETWORKSTREAM_H_
#define LOGGERNETWORKSTREAM_H_

#include "Logger.h"

#include "../network/SocketTCP.h"

namespace cpputil {
namespace logger {

class LoggerNetworkStream: public cpputil::logger::Logger {
public:
enum Protocol {UDP, TCP};

public:
	LoggerNetworkStream(Protocol protocol,
						std::string ipAddres,
						unsigned short portNumber,
						Logger::LoggerLvl loggerLvl);

	virtual void internalMessage(std::string completeMessage, Logger::LoggerLvl lvl);

	virtual ~LoggerNetworkStream();

private:
	void connectToLoggerServer();

private:
	Protocol protocol;
	std::string idAddres;
	unsigned short portNumber;
	cpputil::network::SocketTCP* socketTCP;
};

} /* namespace logger */
} /* namespace cpputil */
#endif /* LOGGERNETWORKSTREAM_H_ */
