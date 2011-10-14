/*
 * NotImplementedException.h
 *
 *  Created on: Sep 14, 2011
 *      Author: caioviel
 */

#ifndef NOTIMPLEMENTEDEXCEPTION_H_
#define NOTIMPLEMENTEDEXCEPTION_H_

#include "SimpleException.h"

namespace cpputil {

class NotImplementedException: public cpputil::SimpleException {
public:
	NotImplementedException(std::string e, std::string c, std::string m) :
		SimpleException(e, c, m) {

		setExceptionSign("cpputil::NotImplementedException");
	}
};

} /* namespace cpputil */
#endif /* NOTIMPLEMENTEDEXCEPTION_H_ */
