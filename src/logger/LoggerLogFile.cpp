/*
 * LoggerLogFile.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: caioviel
 */

#include "../../include/logger/LoggerLogFile.h"

#include <cerrno>
#include <cstring>
using namespace std;

namespace cpputil {
namespace logger {

LoggerLogFile::LoggerLogFile(string _fileName, WriteMode _writemode, Logger::LoggerLvl loggerLvl) :
	Logger (loggerLvl) {

	this->fileName = _fileName;
	this->writemode = _writemode;

	if (writemode == LoggerLogFile::OVERWRITE_FILE) {
		file.open(fileName.c_str(), fstream::out | fstream::trunc);
	} else if (writemode == LoggerLogFile::APPEND_FILE) {
		file.open(fileName.c_str(), fstream::out | fstream::app);
	}

	if (file.fail()) {
		string men = "Error trying to open the file: ";
		men += strerror( errno );
		LoggerException(
				men,
				"cpputil::logger::LoggerLogFile",
				"[Constructor] LoggerLogFile(string, WriteMode, LoggerLvl");
	}
}

void LoggerLogFile::internalMessage(string completeMessage, LoggerLvl lvl) {
	file<<completeMessage<<endl;
}

} /* namespace logger */
} /* namespace cpputil */
