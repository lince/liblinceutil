/*
 * LoggerXmlParser.h
 *
 *  Created on: Jul 20, 2011
 *      Author: caioviel
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
using namespace std;

#include <ticpp/ticpp.h>
using namespace ticpp;

#include "LoggerException.h"
#include "LoggerManager.h"

#ifndef LOGGERXMLPARSER_H_
#define LOGGERXMLPARSER_H_

namespace cpputil {
namespace logger {

class LoggerXmlParser {
public:
	LoggerXmlParser(string xmlFileName);
	void parseDocument();
	virtual ~LoggerXmlParser();

    set<string>* getBlockedClasses();
    string getFileName();
    string getIpAddress();
    LoggerManager::LoggerStyle getLoggerStyle();
    unsigned short getPortNumber();
    LoggerManager::RegionalOpt getRegional();
    LoggerNetworkStream::Protocol getProtocol();
    LoggerLogFile::WriteMode getWritemode();
    Logger::LoggerLvl getLoggerLvl();
    LoggerColor::Color* getColors();

private:
    void parseBlockedClasses(Element* blockedClasses);
    void parseNetworkStream(Element* style);
    void parseLogFile(Element* style);
    void parseDefault(Element* style);
    void parseColor(Element* style);

private:
    string xmlFileName;
	set<string>* blockedClasses;
	LoggerManager::RegionalOpt regionalOpt;
	LoggerManager::LoggerStyle loggerStyle;
	Logger::LoggerLvl loggerLvl;

	string ipAddress;
	unsigned short	portNumber;
	LoggerNetworkStream::Protocol protocol;

	string logfileName;
	LoggerLogFile::WriteMode writemode;

	LoggerColor::Color* colors;

	void resetDefault();
};

} /* namespace logger */
} /* namespace cpputil */
#endif /* LOGGERXMLPARSER_H_ */
