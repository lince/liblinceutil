/*
 * LoggerDefault.h
 *
 *  Created on: Jul 20, 2011
 *      Author: caioviel
 */

#ifndef LOGGERDEFAULT_H_
#define LOGGERDEFAULT_H_

#include "Logger.h"

namespace cpputil {
namespace logger {

class LoggerDefault : public Logger {
public:
	LoggerDefault(Logger::LoggerLvl loggerLvl);

protected:
	virtual void internalMessage(std::string completeMessage, LoggerLvl lvl);
};

} /* namespace logger */
} /* namespace cpputil */
#endif /* LOGGERDEFAULT_H_ */
