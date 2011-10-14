#include <iostream>
using namespace std;

#include "../include/logger/LoggerManager.h"
#include "../include/logger/LoggerException.h"
using namespace cpputil::logger;

class LoggableClass0 : public Loggable {
private:
	virtual void callBackLogger() {

	}
	Logger* logger;

public:
	LoggableClass0() : Loggable("LoggableClass0") {
		trace("constructor");
	}

	void doSomething() {
		trace("Begin doSomething()");
		warning("Warning Message");
		error("Error Message");
		trace("End doSomething()");
	}

};

class LoggableClass1 : public Loggable {
private:
	virtual void callBackLogger() {

	}
	Logger* logger;

public:
	LoggableClass1() {
		logger = Logger::getInstance();
		REGISTER(logger, "LoggableClass1");
		TRACE(logger, "Begin Constructor");
		TRACE(logger, "End Constructor");
	}

	void doSomethingElse() {
		TRACE(logger, "Begin doSomethingElse()");
		INFO(logger,"Info Message");
		DEBUG(logger, "Debug Message");
		TRACE(logger, "End doSomethingElse()");

	}

	void doSomething() {
		TRACE(logger, "Begin doSomething()");
		WARNING(logger, "Warning Message");
		doSomethingElse();
		ERROR(logger, "Error Message");
		TRACE(logger, "End doSomething()");
	}

};

int main() {

	try {
		LoggerManager* lm = LoggerManager::getInstance();
		lm->readConfigurationFile("config.xml");
		Logger* logger = Logger::getInstance();
		logger->traceMessage("Trace test");
		logger->debugMessage("Debug test");
		logger->infoMessage("Info test");
		logger->warningMessage("Warning test");
		logger->errorMessage("Error test");
		logger->fatalMessage("Fatal test");
		LoggableClass0 l0;
		l0.doSomething();
		LoggableClass1 l1;
		l1.doSomething();
		/*while (true) {
			logger->warningMessage("Periodic message");
			usleep(500);
		}*/
	} catch (LoggerException &ex) {
		cout << ex.what();
	}

	return 0;
}
