/*
 * SimpleException.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: caioviel
 */

#include "../include/SimpleException.h"

namespace cpputil {

SimpleException::SimpleException(
		std::string e, std::string c, std::string m) :  errorMsg(e), classStr(c), methodStr(m) {

	setExceptionSign("cpputil::SimpleException");
}

SimpleException::~SimpleException() throw() {

}

void SimpleException::setExceptionSign(std::string exceptionSign) {
	this->exceptionSign = exceptionSign;
}

std::string SimpleException::getClassName() {
	return classStr;
}

std::string SimpleException::getMethodName() {
	return methodStr;
}

std::string SimpleException::getErrorMessage() {
	return errorMsg;
}

std::string SimpleException::getExceptionSign() {
	return exceptionSign;
}

const char* SimpleException::what() const throw() {
	std::string fullMsg = "A '";
	fullMsg += exceptionSign;
	fullMsg += "' has been throwed by class <";
	fullMsg += classStr;
	fullMsg += "> at method <";
	fullMsg += methodStr;
	fullMsg += ">\n\terror message: ";
	fullMsg += errorMsg + "\n";
	return fullMsg.c_str();
}

} /* namespace cpputil */
