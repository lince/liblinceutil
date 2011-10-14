/*
 * colortest.cpp
 *
 *  Created on: Sep 16, 2011
 *      Author: caioviel
 */

#include <iostream>
#include <sstream>

using namespace std;

class Test {
public:
	void saida(std::basic_ostream<char>& stream);
};

void Test::saida(std::basic_ostream<char>& stream) {
	/*cout << stream.str();*/
	stringstream s = static_cast<stringstream> (stream);
	cout << s.str();
}

int main() {

	Test test;
	test.saida((stringstream stream<<"caio " << "Cedar" << "viel"));

	return 0;
}




