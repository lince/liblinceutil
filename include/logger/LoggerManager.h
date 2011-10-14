/*
 * LoggerManager.h
 *
 *  Created on: Jul 20, 2011
 *      Author: caioviel
 */

#ifndef LOGGERMANAGER_H_
#define LOGGERMANAGER_H_

#include <string>
#include <set>

#include "Logger.h"
#include "LoggerDefault.h"
#include "LoggerLogFile.h"
#include "LoggerNetworkStream.h"
#include "LoggerColor.h"

namespace cpputil {
namespace logger {

typedef int LOGGER_STYLE;


class LoggerManager {
public:
	enum LoggerStyle {
		DEFAULT,
		LOGFILE,
		NETWORKSTREAM,
		MULTILOGGER,
		COLOR};
    enum RegionalOpt{ USA, BRAZIL};

private:
    LoggerManager();

public:
    virtual ~LoggerManager();
    static LoggerManager *getInstance();

    void readConfigurationFile(std::string filePath);

    void addBlockedClassList(std::string completeClassName);
    bool removeBlockedClassList(std::string completeClassName);
    bool isBlockedClass(std::string completeClassName);

    RegionalOpt getRegionalOpt();
    void setRegionalOpt(RegionalOpt regionalOpt);

    void setLoggerLvl(Logger::LoggerLvl loggerLvl);
    Logger::LoggerLvl getLoggerLvl();

    void setLoggerStyle(LoggerStyle loggerStyle);
    LoggerStyle getLoggerStyle();

    std::string getIpAddress();
    std::string getLogfileName();
    unsigned short getPortNumber();
    LoggerNetworkStream::Protocol getProtocol();
    LoggerLogFile::WriteMode getWritemode();

    void setIpAddress(std::string ipAddress);
    void setLogfileName(std::string logfileName);
    void setPortNumber(unsigned short  portNumber);
    void setProtocol(LoggerNetworkStream::Protocol  protocol);
    void setWritemode(LoggerLogFile::WriteMode  writemode);

    void setLevelColor(Logger::LoggerLvl lvl, LoggerColor::Color color);
    LoggerColor::Color getLevelColor(Logger::LoggerLvl lvl);

    static RegionalOpt stringToRegionalOpt(std::string str);
    static std::string regionalOptToString(RegionalOpt regionalOpt);
    static LoggerStyle stringToLoggerStyle(std::string str);
    static std::string loggerStyleToString(LoggerStyle loggerStyle);

private:
    static LoggerManager* _instance;
    static Logger* loggerInstance;

    Logger::LoggerLvl loggerLvl;
    std::set<std::string>* blockedClassList;
	LoggerStyle loggerStyle;
	RegionalOpt regionalOpt;

	std::string ipAddress;
	unsigned short	portNumber;
	LoggerNetworkStream::Protocol protocol;

	std::string logfileName;
	LoggerLogFile::WriteMode writemode;

	LoggerColor::Color* colors;

private:
	Logger* CreateLoggerInstance();

friend class Logger;
};

} /* namespace logger */
} /* namespace cpputil */
#endif /* LOGGERMANAGER_H_ */
