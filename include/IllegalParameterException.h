#ifndef ILLEGALPARAMETEREXPECTION_H_
#define ILLEGALPARAMETEREXPECTION_H_

#include "SimpleException.h"

namespace cpputil {

class IllegalParameterException : public cpputil::SimpleException  {
public:
	IllegalParameterException(std::string e, std::string c, std::string m) :
			SimpleException (e, c, m){

		setExceptionSign("cpputil::IllegalParameterException");
	}
};

} /* namespace cpputil */
#endif /* ILLEGALPARAMETEREXPECTION_H_ */
