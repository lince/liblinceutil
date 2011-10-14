/*
 * LoggerLogFile.h
 *
 *  Created on: Jul 21, 2011
 *      Author: caioviel
 */

#ifndef LOGGERLOGFILE_H_
#define LOGGERLOGFILE_H_

#include <fstream>

#include "Logger.h"

namespace cpputil {
namespace logger {

class LoggerLogFile: public cpputil::logger::Logger {

public:

enum WriteMode {
	APPEND_FILE,
	OVERWRITE_FILE,
};

public:
	LoggerLogFile(std::string fileName, WriteMode writemode, Logger::LoggerLvl loggerLvl);

protected:
	virtual void internalMessage(std::string completeMessage, LoggerLvl lvl);

private:
	WriteMode writemode;
	std::string fileName;
	std::fstream file;
};

} /* namespace logger */
} /* namespace cpputil */
#endif /* LOGGERLOGFILE_H_ */
