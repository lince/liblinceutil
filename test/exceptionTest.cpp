#include <iostream>
using namespace std;


#include "../include/SimpleException.h"
using namespace cpputil;

class MyException : public SimpleException {
public:
	MyException(string e, string c, string m) : SimpleException(e,c,m) {
		setExceptionSign("MyException");
	}
};

class MyNewException : public MyException {
public:
	MyNewException(string e, string c, string m) : MyException(e,c,m) {
		setExceptionSign("MyNewException");
	}
};

void doSomething() {
	try {
		throw SimpleException(
				"Dummy error message - Cascade throw and catch",
				"Main.Class",
				"void doSomething()");
	} catch (SimpleException &ex) {
		throw ex;
	}
}

int main() {

	/* Simplest throw and catch */
	try {
		throw SimpleException("Dummy error message - Simplest throw and catch");
	} catch (SimpleException &ex) {
		cout << ex.what();
	}

	/* Not so simple throw and catch */
	try {
		throw SimpleException(
				"Dummy error message - Not so simple throw and catch",
				"Main.Class",
				"int main()");
	} catch (SimpleException &ex) {
		cout << ex.what();
	}

	/* Cascade throw and catch */
	try {
		doSomething();
	} catch (SimpleException &ex) {
		cout << ex.what();
	}

	/* Extending the SimpleExceptin and priority catch test*/
	try {
		throw MyException(
						"Dummy error message - Extending the SimpleExceptin and priority catch test",
						"Main.Class",
						"int main()");
	} catch (MyNewException &ex) {
		cout << "MyNewException was catch:" << ex.what();
	} catch (MyException &ex) {
		cout << "MyException was catch:" << ex.what();
	} catch (SimpleException &ex) {
		cout << "SimpleException was catch:" << ex.what();
	}

	/* Extending the extended SimpleException and mistyped catch*/
	try {
		throw MyNewException(
				"Dummy error message - Extending the extended SimpleException and mistyped catch",
				"Main.Class",
				"int main()");
	} catch (MyException &ex) {
		cout << ex.what();
	}

	return 0;
}
