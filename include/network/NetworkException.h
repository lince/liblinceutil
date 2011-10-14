#ifndef NETWORKEXCEPTION_H_
#define NETWORKEXCEPTION_H_

#include "../SimpleException.h"

namespace cpputil {
namespace network {

class NetworkException : public cpputil::SimpleException {
public:
	NetworkException(std::string e, std::string c, std::string m) :
			SimpleException (e, c, m){

		setExceptionSign("cpputil::network::NetworkException");
	}
};


} /* namespace cpputil */
} /* namespace network */
#endif /* NETWORKEXCEPTION_H_ */
