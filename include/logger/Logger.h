/*
 * Logger.h
 *
 *  Created on: Jul 19, 2011
 *      Author: caioviel
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <map>

#include "Loggable.h"
#include "LoggerException.h"

namespace cpputil {
namespace logger {

class LoggerManager;

class Logger {
public:
	enum LoggerLvl {
		TRACE=0,
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		FATAL,
	};

	static Logger* getInstance();
	static std::string loggerLvlToString(LoggerLvl loggerLvl);
	static LoggerLvl stringToLoggerLvl(std::string str);
public:
	void registerClass(Loggable* loggable, std::string completeClassName);
	void unregisterClass(Loggable* loggable);

	virtual ~Logger();

	virtual void message(std::string str, LoggerLvl lvl=INFO, Loggable* _this=NULL);

	virtual void traceMessage(std::string str, Loggable* _this=NULL);
	virtual void debugMessage(std::string str, Loggable* _this=NULL);
	virtual void infoMessage(std::string str, Loggable* _this=NULL);
	virtual void warningMessage(std::string str, Loggable* _this=NULL);
	virtual void errorMessage(std::string str, Loggable* _this=NULL);
	virtual void fatalMessage(std::string str, Loggable* _this=NULL);

#define TRACE(OBJLogger, str) OBJLogger->traceMessage(str, this);
#define DEBUG(OBJLogger, str) OBJLogger->debugMessage(str, this);
#define INFO(OBJLogger, str) OBJLogger->infoMessage(str, this);
#define WARNING(OBJLogger, str) OBJLogger->warningMessage(str, this);
#define ERROR(OBJLogger, str) OBJLogger->errorMessage(str, this);
#define FATAL(OBJLogger, str) OBJLogger->fatalMessage(str, this);
#define REGISTER(OBJLogger, str) OBJLogger->registerClass(this, str);
#define UNREGISTER(OBJLogger) OBJLogger->unregisterClass(this);

private:
	static Logger *_instance;

protected:
	LoggerLvl loggerLvl;
	LoggerManager* logManager;
	std::map<Loggable*, std::string>* loggableMap;

protected:
	Logger(LoggerLvl loggerLvl);
	virtual std::string getTimeInfo();
	virtual void internalMessage(std::string completeMessage, LoggerLvl lvl) = 0;


friend class LoggerManager;

};

} /* namespace logger */
} /* namespace cpputil */
#endif /* LOGGER_H_ */
