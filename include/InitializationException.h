#ifndef _INITIALIZATIONEXCEPTION_H
#define	_INITIALIZATIONEXCEPTION_H

#include "SimpleException.h"

namespace cpputil {

/**
 *  Exceção lançanda quando um método é chamado sem que seus pré-requisitos de execução tenham sido satisfeitos.
 *  Alguns métodos possuem pré-requisitos (como inicialização de uma variável, por exemplo). Quando estes métodos
 *  são chamados sem que estes pré-requisitos sejam satisfeitos, eles não devem continuar suas execuções e lançar
 *  uma exceção deste tipo. É interessante que a mensagem da exceção contenha informações sobre quais pré-requisitos
 *  não foram satisfeitos.
 */
class InitializationException : public cpputil::SimpleException {
public:
	InitializationException(std::string e, std::string c, std::string m) :
			SimpleException (e, c, m){

		setExceptionSign("cpputil::InitializationException");
	}
};

} /* namespace cpputil */
#endif	/* _INITIALIZATIONEXCEPTION_H */

