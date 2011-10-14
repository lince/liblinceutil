/*
 * Loggable.h
 *
 *  Created on: Jul 20, 2011
 *      Author: caioviel
 */

#ifndef LOGGABLE_H_
#define LOGGABLE_H_

#include <string>

namespace cpputil {
namespace logger {

class Logger;

class Loggable {
public:
	Loggable();

	Loggable(std::string className);

	virtual ~Loggable();

	/* must be implemented by all class */
	virtual void callBackLogger();

protected:
	void trace(std::string str);
	void debug(std::string str);
	void info(std::string str);
	void warning(std::string str);
	void error(std::string str);
	void fatal(std::string str);
	void unregister();

private:
	Logger* logger;

};



} /* namespace logger */
} /* namespace cpputil */
#endif /* LOGGABLE_H_ */
