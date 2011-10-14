/*
 * LoggerColor.h
 *
 *  Created on: Sep 16, 2011
 *      Author: caioviel
 */

#ifndef LOGGERCOLOR_H_
#define LOGGERCOLOR_H_

#include "Logger.h"

namespace cpputil {
namespace logger {

class LoggerColor: public cpputil::logger::Logger {
public:
	enum Color {
		BLACK=0, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN,
		GRAY, DARK_GRAY, LIGHT_RED, LIGHT_GREEN, YELLOW,
		LIGHT_BLUE, LIGHT_MAGENTA, LIGHT_CYAN, WHITE,
		DEFAULT};

	LoggerColor(Logger::LoggerLvl loggerLvl, Color* colors=NULL);

public:
	static Color stringToColor(std::string str);
	static std::string colorToString(Color color);
	static Color* getDefaultColors();

protected:
	virtual void internalMessage(std::string completeMessage, LoggerLvl lvl);

private:
	static std::string colorsStr[];
	Color* colors;
};

} /* namespace logger */
} /* namespace cpputil */
#endif /* LOGGERCOLOR_H_ */
