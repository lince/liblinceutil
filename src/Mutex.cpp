/*
 * Mutex.cpp
 *
 *  Created on: Sep 19, 2011
 *      Author: caioviel
 */

#include "../include/Mutex.h"
#include "../include/IllegalParameterException.h"

namespace cpputil {

std::map<std::string, Mutex*> Mutex::namedMutex;

Mutex::Mutex() : name("") {
	pthread_mutex_init(&linux_mutex, NULL);
}

Mutex::Mutex(std::string _name) : name (_name) {
	pthread_mutex_init(&linux_mutex, NULL);
	std::map<std::string, Mutex*>::iterator it;
	it = namedMutex.find(name);
	if (it != namedMutex.end()) {
		throw IllegalParameterException(
				"Trying to name a mutex that already exists.",
				"cpputil::Mutex",
				"Mutex(string)");
	}
	namedMutex[name] = this;
}

Mutex::~Mutex() {
	if (name != "") {
		std::map<std::string, Mutex*>::iterator it;
		it = namedMutex.find(name);
		if (it != namedMutex.end()) {
			namedMutex.erase(it);
		}
	}
	pthread_mutex_destroy(&linux_mutex);
}


Mutex* Mutex::getNamedMutex(std::string name) {
	std::map<std::string, Mutex*>::iterator it;
	it = namedMutex.find(name);
	if (it != namedMutex.end()) {
		return it->second;
	}
	return NULL;
}

void Mutex::lock() {
	pthread_mutex_lock(&linux_mutex);
}

void Mutex::unlock() {
	pthread_mutex_unlock(&linux_mutex);

}

} /* namespace cpputil */
