/*
 * Mutex.h
 *
 *  Created on: Sep 19, 2011
 *      Author: caioviel
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <string>
#include <pthread.h>
#include <map>

namespace cpputil {

class Mutex {
public:
	Mutex();

	Mutex(std::string name);

	virtual ~Mutex();

	void lock();

	void unlock();

public:
	static Mutex* getNamedMutex(std::string name);

private:
	pthread_mutex_t linux_mutex;
	std::string name;

	static std::map<std::string, Mutex*> namedMutex;

};

} /* namespace cpputil */
#endif /* MUTEX_H_ */
