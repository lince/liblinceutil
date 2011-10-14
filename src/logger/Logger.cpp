/*
 * Logger.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: caioviel
 */

#include "../../include/logger/Logger.h"
#include "../../include/logger/LoggerManager.h"
#include "../../include/logger/LoggerException.h"

#include "../../include/Functions.h"
using namespace cpputil;

using namespace std;

namespace cpputil {
namespace logger {

Logger* Logger::_instance = NULL;

Logger::Logger(LoggerLvl loggerLvl) {
	if (loggerLvl > FATAL || loggerLvl < TRACE) {
		throw LoggerException(
				"Trying to set a invalid logger level value!",
				"cpputil::logger::Logger",
				"[Constructor] Logger(LoggerLvl)");
	}
	this->loggerLvl = loggerLvl;
	loggableMap = new map<Loggable*, string>();
	logManager = NULL;
}

Logger::~Logger() {
	map<Loggable*, string>::iterator it;
	it = loggableMap->begin();
	while (it != loggableMap->end()) {
		Loggable* loggable = it->first;
		delete loggable;
		it++;
	}
	delete loggableMap;
}

Logger *Logger::getInstance() {
	if (_instance == NULL) {
		LoggerManager* loggerManager = LoggerManager::getInstance();
		_instance = loggerManager->CreateLoggerInstance();
		_instance->logManager = loggerManager;
	}
	return _instance;
}

void Logger::registerClass(Loggable* loggable, string completeClassName) {
	map<Loggable*, string>::iterator it;
	it = loggableMap->find(loggable);
	if (it != loggableMap->end()) {
		throw LoggerException(
				"Trying to register the same Loggable instance twice!",
				"cpputil::logger::Logger",
				"registerClass(Loggable*, string)");
	}
	//TODO: verificar se o nome da classe é válido
	loggableMap->insert(pair<Loggable*, string>(loggable, completeClassName) );
}

void Logger::unregisterClass(Loggable *loggable) {
	map<Loggable*, string>::iterator it;
	it = loggableMap->find(loggable);
	if (it == loggableMap->end()) {
		throw LoggerException(
				"Trying to unregister a not registrad Loggable instance!",
				"cpputil::logger::Logger",
				"unregisterClass(Loggable*)");
	}
	loggableMap->erase(it);
}

void Logger::traceMessage(string str, Loggable *_this) {
	message(str, TRACE, _this);
}

void Logger::debugMessage(string str, Loggable *_this) {
	message(str, DEBUG, _this);
}

void Logger::infoMessage(string str, Loggable *_this) {
	message(str, INFO, _this);
}

void Logger::warningMessage(string str, Loggable *_this) {
	message(str, WARNING, _this);
}

void Logger::errorMessage(string str, Loggable *_this) {
	message(str, ERROR, _this);
}

void Logger::fatalMessage(string str, Loggable *_this) {
	message(str, FATAL, _this);
}

string Logger::getTimeInfo() {
	LoggerManager::RegionalOpt regionalOpt = logManager->getRegionalOpt();
	switch(regionalOpt) {
	case LoggerManager::USA:
		return Functions::getCurrentTimestampUS();
	case LoggerManager::BRAZIL:
		return Functions::getCurrentTimestampBR();
	default:
		return Functions::getCurrentTimestampUS();
		break;
	}
	return "";
}

void Logger::message(string str, LoggerLvl lvl, Loggable *_this) {
	string completeClassName;
	string completeMessage = "";
	bool hasClassName = false;

	if (lvl < loggerLvl) {
		return; /*message level to low*/
	}

	if (_this != NULL) {
		map<Loggable*, string>::iterator it = loggableMap->find(_this);
		if (it != loggableMap->end()) {
			completeClassName = it->second;
			hasClassName = true;
		} else {
			return; /*loggable class name doesn't exist, just ignore*/
			//TODO this is a error, maybe must be logged.
		}
	} else {
		completeClassName = "No class info given";
	}

	if (hasClassName) {
		if (logManager->isBlockedClass(completeClassName)) {
			return; /* loggable class is blocked */
		}
	}

	completeMessage = getTimeInfo();
	completeMessage += ": ";
	completeMessage += completeClassName;
	completeMessage += " [" + loggerLvlToString(lvl) + "] - ";
	completeMessage += str;
	internalMessage(completeMessage, lvl);
}

string Logger::loggerLvlToString(LoggerLvl loggerLvl) {
	switch(loggerLvl) {
		case Logger::TRACE: return "TRACE";
		case Logger::DEBUG: return "DEBUG";
		case Logger::INFO: return "INFO";
		case Logger::WARNING: return "WARNING";
		case Logger::ERROR: return "ERROR";
		case Logger::FATAL: return "FATAL";
		default: return "INFO";
	}
}

Logger::LoggerLvl Logger::stringToLoggerLvl(string str) {
	if (str == "trace" || str== "TRACE") {
		return Logger::TRACE;
	} else if (str == "debug" || str== "DEBUG") {
		return Logger::DEBUG;
	} else if (str == "info" || str== "INFO") {
		return Logger::INFO;
	} else if (str == "warning" || str== "WARNING") {
		return Logger::WARNING;
	} else if (str == "error" || str== "ERROR") {
		return Logger::ERROR;
	} else if (str == "fatal" || str== "FATAL") {
		return Logger::TRACE;
	} else {
		throw LoggerException(
				"Trying to convert a invalid string.",
				"cpputil::logger::Logger",
				"stringToLoggerLvl(string)");
	}
}

} /* namespace logger */
} /* namespace cpputil */
