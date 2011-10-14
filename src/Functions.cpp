/*
 * Functions.cpp
 *
 *  Created on: Jul 15, 2011
 *      Author: caioviel
 */

#include "../include/Functions.h"
#include <sstream>
#include <ctime>
#include <ctype.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/timeb.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
using namespace std;

namespace cpputil {

inline string Functions::numberToString(double value) {
	stringstream out;
	out << value;
	string s = out.str();
	return s;
}

Date *Functions::getCurrentDate() {
	time_t rawtime;
	struct tm * timeinfo;
	Date* date = new Date();

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	date->day = timeinfo->tm_mday;
	date->mounth = timeinfo->tm_mon + 1;
	date->year = timeinfo->tm_year + 1900;

	//delete timeinfo;
	return date;
}



Time *Functions::getCurrentTime() {
	time_t rawtime;
	struct tm * timeinfo;
	Time* nTime = new Time();

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	nTime->hour  = timeinfo->tm_hour;
	nTime->minute = timeinfo->tm_min;
	nTime->second = timeinfo->tm_sec;

	//delete timeinfo;
	return nTime;
}

string Functions::timeToStringUS(Time *time) {
	string aux = "";
	if (time->hour <= 12) {
		if (time->hour < 10) {
			aux += "0";
		}
		aux += Functions::numberToString(time->hour) + ":";
		if (time->minute < 10) {
			aux += "0";
		}
		aux += Functions::numberToString(time->minute) + ":";
		if (time->second < 10) {
			aux += "0";
		}
		aux += Functions::numberToString(time->second) + " AM";
	} else {
		if (time->hour < 10) {
			aux += "0";
		}
		aux = Functions::numberToString(time->hour - 12) + ":";
		if (time->minute < 10) {
			aux += "0";
		}
		aux += Functions::numberToString(time->minute) + ":";
		if (time->minute < 10) {
			aux += "0";
		}
		aux += Functions::numberToString(time->second) + " PM";
	}
	return aux;
}

string Functions::timeToStringBR(Time *time) {
	string aux = "";
	if (time->hour < 10) {
		aux += "0";
	}
	aux += Functions::numberToString(time->hour) + ":";
	if (time->minute < 10) {
		aux += "0";
	}
	aux += Functions::numberToString(time->minute) + ":";
	if (time->second < 10) {
		aux += "0";
	}
	aux += Functions::numberToString(time->second);
	return aux;
}

string Functions::dateToStringUS(Date *date) {
	string aux = "";
	if (date->mounth < 10) {
		aux += "0";
	}
	aux += Functions::numberToString(date->mounth) + "/";
	if (date->day < 10) {
		aux += "0";
	}
	aux += Functions::numberToString(date->day) + "/";
	aux += Functions::numberToString(date->year);
	return aux;
}

string Functions::dateToStringBR(Date *date) {
	string aux = "";
	if (date->day < 10) {
		aux += "0";
	}
	aux += Functions::numberToString(date->day) + "/";
	if (date->mounth < 10) {
		aux += "0";
	}
	aux += Functions::numberToString(date->mounth) + "/";
	aux += Functions::numberToString(date->year);
	return aux;
}

string Functions::getCurrentTimestampUS() {
	time_t rawtime;
	struct tm * timeinfo;
	Date* date = new Date();
	Time* nTime = new Time();
	string aux;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	date->day = timeinfo->tm_mday;
	date->mounth = timeinfo->tm_mon + 1;
	date->year = timeinfo->tm_year + 1900;

	nTime->hour  = timeinfo->tm_hour;
	nTime->minute = timeinfo->tm_min;
	nTime->second = timeinfo->tm_sec;

	//delete timeinfo;

	aux = Functions::timeToStringUS(nTime) + " - " +
			Functions::dateToStringUS(date);

	delete nTime;
	delete date;
	return aux;
}

string Functions::getCurrentTimestampBR() {
	time_t rawtime;
	struct tm * timeinfo;
	Date* date = new Date();
	Time* nTime = new Time();
	string aux;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	date->day = timeinfo->tm_mday;
	date->mounth = timeinfo->tm_mon + 1;
	date->year = timeinfo->tm_year + 1900;

	nTime->hour  = timeinfo->tm_hour;
	nTime->minute = timeinfo->tm_min;
	nTime->second = timeinfo->tm_sec;

	//delete timeinfo;

	aux = Functions::timeToStringBR(nTime) + " - " +
			Functions::dateToStringBR(date);

	delete nTime;
	delete date;
	return aux;
}

double Functions::getCurrentTimeMillis() {
	static double startTimeMills;
	static bool firstCallTimeMills = true;
	timeval result;
	rusage usage;
	timeb t;

	ftime(&t);
	if(firstCallTimeMills) {
		firstCallTimeMills = false;
		startTimeMills = (double)t.time*1000 + (double)t.millitm - 1;
		return 1;
	}
	return (double)t.time*1000 + (double)t.millitm - startTimeMills;
}

bool Functions::isIPv4(const char* ip){
    if(ip == NULL) {
        return false;
    } else {
        sockaddr_in sa;
        return (inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1);
    }
}

bool Functions::isIPv6(const char* ip){
    if(ip == NULL) {
        return false;
    } else {
        sockaddr_in6 sa;
        return (inet_pton(AF_INET6, ip, &(sa.sin6_addr)) == 1);
    }
}

}
 /* namespace cpputil */
