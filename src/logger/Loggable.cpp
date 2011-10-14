#include "../../include/logger/Loggable.h"
#include "../../include/logger/Logger.h"

using namespace std;

namespace cpputil {
namespace logger {

Loggable::Loggable() {
	/* This constructor doesn't do nothing. It's only used to keep
	 * compatibility with older interface.
	 */
}

Loggable::Loggable(std::string className) {
	logger = Logger::getInstance();
	REGISTER(logger, className);
}

Loggable::~Loggable() {
	unregister();
}

void Loggable::trace(std::string str) {
	TRACE(logger, str);
}

void Loggable::debug(std::string str) {
	DEBUG(logger, str);
}

void Loggable::info(std::string str) {
	INFO(logger, str);
}

void Loggable::warning(std::string str) {
	WARNING(logger, str);
}

void Loggable::error(std::string str) {
	ERROR(logger, str);
}

void Loggable::fatal(std::string str) {
	ERROR(logger, str);
}

void Loggable::unregister() {
	UNREGISTER(logger);
}

/* must be implemented by all class */
void Loggable::callBackLogger() {

}

}
}
