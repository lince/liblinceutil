/*
 * LoggerDefault.cpp
 *
 *  Created on: Jul 20, 2011
 *      Author: caioviel
 */

#include "../../include/logger/LoggerDefault.h"
#include "../../include/logger/LoggerManager.h"

#include <iostream>
#include <cstdlib>
using namespace std;

namespace cpputil {
namespace logger {

LoggerDefault::LoggerDefault(Logger::LoggerLvl nloggerLvl) : Logger(nloggerLvl) {

}


void LoggerDefault::internalMessage(string completeMessage, LoggerLvl lvl) {
	cout << completeMessage << endl;
}

} /* namespace logger */
} /* namespace cpputil */

 /* namespace tvmonitor */
