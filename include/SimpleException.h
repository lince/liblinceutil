/*
 * SimpleException.h
 *
 *  Created on: Jul 21, 2011
 *      Author: caioviel
 */

#ifndef SIMPLEEXCEPTION_H_
#define SIMPLEEXCEPTION_H_

#include <exception>
#include <string>

namespace cpputil {

class SimpleException : public std::exception {
protected:
	std::string classStr, methodStr, errorMsg;
	virtual void setExceptionSign(std::string exceptionSign);

private:
	std::string exceptionSign;


public:
	SimpleException(
			std::string errorMsg,
			std::string classStr="unspecified",
			std::string methodStr="unspecified");

	virtual ~SimpleException() throw();

	virtual const char* what() const throw();

	virtual std::string getExceptionSign();
	virtual std::string getClassName();
	virtual std::string getMethodName();
	virtual std::string getErrorMessage();
};

} /* namespace cpputil */
#endif /* SIMPLEEXCEPTION_H_ */
