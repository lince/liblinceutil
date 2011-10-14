/*
 * LoggerException.h
 *
 *  Created on: Jul 21, 2011
 *      Author: caioviel
 */

#ifndef LOGGEREXCEPTION_H_
#define LOGGEREXCEPTION_H_

#include "../SimpleException.h"

namespace cpputil {
namespace logger {

class LoggerException: public cpputil::SimpleException {
public:
	LoggerException(std::string e, std::string c, std::string m) :
			SimpleException (e, c, m){
		setExceptionSign("cpputil::logger::LoggerException");
	}

};

} /* namespace logger */
} /* namespace cpputil */
#endif /* LOGGEREXCEPTION_H_ */
