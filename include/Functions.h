/*
 * Functions.h
 *
 *  Created on: Jul 15, 2011
 *      Author: caioviel
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <string>

namespace cpputil {

struct Date {
	int day; /*1-31*/
	int mounth; /*1-12*/
	int year; /*YYYY format*/
};

struct Time {
	int hour; /*0-23*/
	int minute; /*0-59*/
	int second; /*0-59*/
};

class Functions {
public:
	virtual ~Functions() {

	}

	static std::string numberToString(double value);

	static Date* getCurrentDate();
	static Time* getCurrentTime();

	static std::string getCurrentTimestampUS();
	static std::string getCurrentTimestampBR();

	static std::string timeToStringUS(Time* time);
	static std::string timeToStringBR(Time* time);

	static std::string dateToStringUS(Date* date);
	static std::string dateToStringBR(Date* date);

	static double getCurrentTimeMillis();

    /**
     * Verifica se um endereço IP é da versão 4.
     * @param ip endereço IP.
     * @return true, se o endereço passado for da versão 4, ou false, caso contrário.
     */
    static bool isIPv4(const char* ip);

    /**
     * Verifica se um endereço IP é da versão 6.
     * @param ip endereço IP.
     * @return true, se o endereço passado for da versão 6, ou false, caso contrário.
     */
    static bool isIPv6(const char* ip);

};

} /* namespace cpputil */
#endif /* FUNCTIONS_H_ */
