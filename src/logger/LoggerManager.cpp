/*
 * LoggerManager.cpp
 *
 *  Created on: Jul 20, 2011
 *      Author: caioviel
 */

#include "../../include/logger/LoggerManager.h"
#include "../../include/logger/LoggerXmlParser.h"

using namespace std;

namespace cpputil {
namespace logger {

LoggerManager* LoggerManager::_instance = NULL;

Logger* LoggerManager::loggerInstance = NULL;

LoggerManager::LoggerManager() {
	loggerStyle = LoggerManager::DEFAULT;
	regionalOpt = LoggerManager::USA;
	loggerLvl = Logger::INFO;
	blockedClassList = new set<string>();

	regionalOpt = LoggerManager::USA;
	loggerStyle = LoggerManager::DEFAULT;
	loggerLvl = Logger::INFO;

	protocol = LoggerNetworkStream::UDP;
	ipAddress = "127.0.0.1";
	portNumber = 5004;

	logfileName = "logfile.log";
	writemode = LoggerLogFile::OVERWRITE_FILE;

	colors = NULL;
}

LoggerManager::~LoggerManager() {
	delete blockedClassList;
}

LoggerManager *LoggerManager::getInstance() {
	if (_instance == NULL) {
		_instance = new LoggerManager();
	}
	return _instance;
}

void LoggerManager::setLoggerLvl(Logger::LoggerLvl loggerLvl) {
	this->loggerLvl = loggerLvl;
}

Logger::LoggerLvl LoggerManager::getLoggerLvl() {
	return loggerLvl;
}

void LoggerManager::readConfigurationFile(string filePath) {
	//TODO: verificar se o filePath é um nome de arquivo válido
	LoggerXmlParser* xmlParser = new LoggerXmlParser(filePath);
	xmlParser->parseDocument();
	loggerLvl = xmlParser->getLoggerLvl();
	regionalOpt = xmlParser->getRegional();
	loggerStyle = xmlParser->getLoggerStyle();

	delete blockedClassList;
	blockedClassList = xmlParser->getBlockedClasses();

	protocol = xmlParser->getProtocol();
	ipAddress = xmlParser->getIpAddress();
	portNumber = xmlParser->getPortNumber();

	logfileName = xmlParser->getFileName();
	writemode = xmlParser->getWritemode();

	if (colors != NULL) {
		delete colors;
	}
	colors = xmlParser->getColors();

	delete xmlParser;
}

void LoggerManager::addBlockedClassList(string completeClassName) {
	//TODO verificar se o nome da classe está dentro dos padrãoes, senão exception.
	blockedClassList->insert(completeClassName);
}

bool LoggerManager::removeBlockedClassList(string completeClassName) {
	set<string>::iterator it;
	it = blockedClassList->find(completeClassName);
	if (it != blockedClassList->end()) {
		blockedClassList->erase(it);
		return true;
	}
	return false;
}

void LoggerManager::setLoggerStyle(LoggerManager::LoggerStyle loggerStyle) {
	this->loggerStyle = loggerStyle;
}

LoggerManager::LoggerStyle LoggerManager::getLoggerStyle() {
	return loggerStyle;
}

bool LoggerManager::isBlockedClass(string completeClassName) {
	set<string>::iterator it;
	it = blockedClassList->find(completeClassName);
	if (it != blockedClassList->end()) {
		return true;
	}
	return false;
}

LoggerManager::RegionalOpt LoggerManager::getRegionalOpt() {
	return regionalOpt;
}

void LoggerManager::setRegionalOpt(RegionalOpt regionalOpt) {
	this->regionalOpt = regionalOpt;
}

LoggerManager::RegionalOpt LoggerManager::stringToRegionalOpt(string str) {
	if (str == "usa" || str== "USA") {
		return LoggerManager::USA;
	} else if (str == "brazil" || str== "BRAZIL") {
		return LoggerManager::BRAZIL;
	} else {
		throw LoggerException(
				"Trying to covert a invalid string to RegionalOpt",
				"cpputil::logger::LoggerManager",
				"stringToRegionalOpt(string)");
	}
}

string LoggerManager::regionalOptToString(RegionalOpt regionalOpt) {
	switch(regionalOpt) {
		case LoggerManager::USA: return "USA";
		case LoggerManager::BRAZIL: return "BRASIL";
		default: return "USA";
	}
}

LoggerManager::LoggerStyle LoggerManager::stringToLoggerStyle(string str) {
	if (str == "default" || str== "DEFAULT") {
		return LoggerManager::DEFAULT;
	} else if (str == "networkstream" || str== "NETWORKSTREAM") {
		return LoggerManager::NETWORKSTREAM;
	} else if (str == "logfile" || str== "LOGFILE") {
		return LoggerManager::LOGFILE;
	} else if (str == "color" || str== "COLOR") {
		return LoggerManager::COLOR;
	} else if (str == "multilogger" || str== "MULTILOGGER") {
		return LoggerManager::MULTILOGGER;
	} else {
		throw LoggerException(
				"Trying to covert a invalid string to Logger Style",
				"cpputil::logger::LoggerManager",
				"stringToLoggerStyle(string)");
	}
}

string LoggerManager::loggerStyleToString(LoggerStyle loggerStyle) {
	switch(loggerStyle) {
		case LoggerManager::DEFAULT: return "DEFAULT";
		case LoggerManager::NETWORKSTREAM: return "NETWORKSTREAM";
		case LoggerManager::LOGFILE: return "LOGFILE";
		case LoggerManager::COLOR: return "COLOR";
		case LoggerManager::MULTILOGGER: return "MULTILOGGER";
		default: return "DEFAULT";
	}
}

string LoggerManager::getIpAddress() {
	return ipAddress;
}

string LoggerManager::getLogfileName() {
	return logfileName;
}

unsigned short LoggerManager::getPortNumber() {
	return portNumber;
}

LoggerNetworkStream::Protocol LoggerManager::getProtocol() {
	return protocol;
}

LoggerLogFile::WriteMode LoggerManager::getWritemode() {
	return writemode;
}

void LoggerManager::setIpAddress(string ipAddress) {
	this->ipAddress = ipAddress;
}

void LoggerManager::setLogfileName(string logfileName) {
	this->logfileName = logfileName;
}

void LoggerManager::setPortNumber(unsigned short  portNumber) {
	this->portNumber = portNumber;
}

void LoggerManager::setProtocol(LoggerNetworkStream::Protocol protocol) {
	this->protocol = protocol;
}

void LoggerManager::setWritemode(LoggerLogFile::WriteMode  writemode) {
	this->writemode = writemode;
}

Logger *LoggerManager::CreateLoggerInstance() {
	if (loggerInstance == NULL) {
		switch(loggerStyle) {
		case LoggerManager::DEFAULT:
			loggerInstance = new LoggerDefault(getLoggerLvl());
			break;
		case LoggerManager::LOGFILE:
			loggerInstance = new LoggerLogFile(getLogfileName(), getWritemode(), getLoggerLvl());
			break;
		case LoggerManager::COLOR:
			loggerInstance = new LoggerColor(getLoggerLvl(), colors);
			break;
		case LoggerManager::NETWORKSTREAM:
			loggerInstance = new LoggerNetworkStream(getProtocol(), getIpAddress(),
					getPortNumber(), getLoggerLvl());
			break;
		}
	}
	return loggerInstance;
}

void LoggerManager::setLevelColor(
		Logger::LoggerLvl lvl, LoggerColor::Color color) {

	if (colors == NULL) {
		colors = LoggerColor::getDefaultColors();
	}
	colors[(int) lvl] = color;
}

LoggerColor::Color LoggerManager::getLevelColor(Logger::LoggerLvl lvl) {
	if (colors == NULL) {
		colors = LoggerColor::getDefaultColors();
	}
	return colors[(int) lvl];
}

} /* namespace logger */
} /* namespace cpputil */
