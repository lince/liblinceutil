/*
 * LoggerColor.cpp
 *
 *  Created on: Sep 16, 2011
 *      Author: caioviel
 */

#include "../../include/logger/LoggerColor.h"
#include "../../include/logger/LoggerException.h"

#include <iostream>
using namespace std;

namespace cpputil {
namespace logger {

string LoggerColor::colorsStr[] = {
			"\033[22;30m",
			"\033[22;31m",
			"\033[22;32m",
			"\033[22;33m",
			"\033[22;34m",
			"\033[22;35m",
			"\033[22;36m",
			"\033[22;37m",
			"\033[01;30m",
			"\033[01;31m",
			"\033[01;32m",
			"\033[01;33m",
			"\033[01;34m",
			"\033[01;35m",
			"\033[01;36m",
			"\033[01;37m",
			"\033[0m",
};

LoggerColor::LoggerColor(
		Logger::LoggerLvl loggerLvl, Color* _colors) : Logger(loggerLvl) {

	this->colors = LoggerColor::getDefaultColors();
	/* using default value */
	if (_colors != NULL) {
		/* using user specified values */
		for (int i=0; i < 6; i++) {
			colors[i] = _colors[i];
		}
	}

}

void LoggerColor::internalMessage(string completeMessage, LoggerLvl lvl) {
	std::cout << colorsStr[(int) colors[(int) lvl]];
	std::cout << completeMessage;
	std::cout << colorsStr[(int) LoggerColor::DEFAULT] << std::endl;
}

LoggerColor::Color LoggerColor::stringToColor(string str) {
	if (str == "black" || str== "BLACK") {
		return LoggerColor::BLACK;
	} else if (str == "red" || str== "RED") {
		return LoggerColor::RED;
	} else if (str == "green" || str== "GREEN") {
		return LoggerColor::GREEN;
	} else if (str == "brown" || str== "BROWN") {
		return LoggerColor::BROWN;
	} else if (str == "blue" || str== "BLUE") {
		return LoggerColor::BLUE;
	} else if (str == "magenta" || str== "MAGENTA") {
		return LoggerColor::MAGENTA;
	} else if (str == "cyan" || str== "CYAN") {
		return LoggerColor::CYAN;
	} else if (str == "gray" || str== "GRAY") {
		return LoggerColor::GRAY;
	} else if (str == "dark_gray" || str== "DARK_GRAY") {
		return LoggerColor::DARK_GRAY;
	} else if (str == "light_red" || str== "LIGHT_RED") {
		return LoggerColor::LIGHT_RED;
	} else if (str == "light_green" || str== "LIGHT_GREEN") {
		return LoggerColor::LIGHT_GREEN;
	} else if (str == "yellow" || str== "YELLOW") {
		return LoggerColor::YELLOW;
	} else if (str == "light_blue" || str== "LIGHT_BLUE") {
		return LoggerColor::LIGHT_BLUE;
	} else if (str == "light_magenta" || str== "LIGHT_MAGENTA") {
		return LoggerColor::LIGHT_MAGENTA;
	} else if (str == "light_cyan" || str== "LIGHT_CYAN") {
		return LoggerColor::LIGHT_CYAN;
	} else if (str == "white" || str== "WHITE") {
		return LoggerColor::WHITE;
	} else if (str == "default" || str== "DEFAULT") {
		return LoggerColor::DEFAULT;
	} else {
		throw LoggerException(
				"Trying to convert a invalid string.",
				"cpputil::logger::Logger",
				"stringToLoggerLvl(string)");
	}

}

string LoggerColor::colorToString(LoggerColor::Color color){
	switch(color) {
		case LoggerColor::BLACK: return "BLACK";
		case LoggerColor::RED: return "RED";
		case LoggerColor::GREEN: return "GREEN";
		case LoggerColor::BLUE: return "BLUE";
		case LoggerColor::BROWN: return "BROWN";
		case LoggerColor::MAGENTA: return "MAGENTA";
		case LoggerColor::CYAN: return "CYAN";
		case LoggerColor::GRAY: return "GRAY";
		case LoggerColor::DARK_GRAY: return "DARK_GRAY";
		case LoggerColor::LIGHT_RED: return "LIGHT_RED";
		case LoggerColor::LIGHT_GREEN: return "LIGHT_GREEN";
		case LoggerColor::YELLOW: return "YELLOW";
		case LoggerColor::LIGHT_BLUE: return "LIGHT_BLUE";
		case LoggerColor::LIGHT_MAGENTA: return "LIGHT_MAGENTA";
		case LoggerColor::LIGHT_CYAN: return "LIGHT_CYAN";
		case LoggerColor::WHITE: return "WHITE";
		default: return "DEFAULT";
	}
}

LoggerColor::Color* LoggerColor::getDefaultColors() {
	Color* colors = new Color[6]();
	colors[0] = LoggerColor::GRAY;
	colors[1] = LoggerColor::GRAY;
	colors[2] = LoggerColor::DEFAULT;
	colors[3] = LoggerColor::YELLOW;
	colors[4] = LoggerColor::LIGHT_RED;
	colors[5] = LoggerColor::RED;
	return colors;
}

} /* namespace logger */
} /* namespace cpputil */
