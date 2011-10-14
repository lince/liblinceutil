#include "../include/Thread.h"
#include "../include/Functions.h"
#include "../include/Mutex.h"
using namespace cpputil;

#include "../include/network/ServerSocketTCP.h"
#include "../include/network/SocketTCP.h"
using namespace cpputil::network;

#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <vector>
using namespace std;


class RemoteLogger : public Thread {
public:
	RemoteLogger(SocketTCP* socketTCP, string loggerID="");

	virtual ~RemoteLogger();

	virtual void run();

	void stop();

private:
	SocketTCP* s;
	string loggerID;
	bool running;
	string colorCommand;

	static int LOGGER_COUNT;
	static string colorsCommands[];
};

string RemoteLogger::colorsCommands[] = {
		"\033[22;30m",
		"\033[22;31m",
		"\033[22;32m",
		"\033[22;33m",
		"\033[22;34m",
		"\033[22;35m",
		"\033[22;36m",
		"\033[22;37m",
		"\033[01;30m",
		"\033[01;31m",
		"\033[01;32m",
		"\033[01;33m",
		"\033[01;34m",
		"\033[01;35m",
		"\033[01;36m",
		"\033[01;37m",
};

int RemoteLogger::LOGGER_COUNT = 0;

RemoteLogger::RemoteLogger(SocketTCP* socketTCP, string loggerID) {
	assert(socketTCP);
	s = socketTCP;
	running = false;

	if (loggerID == "") {
		this->loggerID = (string) "logger_" + Functions::numberToString(LOGGER_COUNT);
	} else {
		this->loggerID = loggerID;
	}
	colorCommand = colorsCommands[(LOGGER_COUNT++)%16];
}

RemoteLogger::~RemoteLogger() {
	if (s != NULL) {
		try {
			s->closeConnection();
		} catch (...) {
			//It have already been closed.
		}
		delete s;
	}
}

void RemoteLogger::stop() {
	running = false;
}

void RemoteLogger::run() {
	running = true;
	Mutex* mutex = Mutex::getNamedMutex("IO_MUTEX");
	try {
		while (running) {
			DataPayload* data = s->receiveData();
			mutex->lock();
			cout << colorCommand << "[" << loggerID << "] \033[0m"
					<< data->getDataAsString() << endl;
			mutex->unlock();
			delete data;
		}
		s->closeConnection();
	} catch (NetworkException& ex) {
		mutex->lock();
		cerr << "Exception catched on RemoteLogger::run() -> " << ex.what() << endl;
		mutex->unlock();
	}
}

int main(int argc, char* argv[]) {
	unsigned int portNumber = 5004;
	vector<RemoteLogger*> remoteLoggers;
	ServerSocketTCP* serverSocket;
	Mutex* mutex = NULL;

	if (argc > 1) {
		portNumber = atoi(argv[0]);
	}

	try {
		cout << "Listing to connections on port " << portNumber << "..." << endl;
		mutex = new Mutex("IO_MUTEX");
		serverSocket = new ServerSocketTCP(portNumber);
		serverSocket->bindPort();
		serverSocket->startListen();
		while (true) {
			SocketTCP* s = serverSocket->acceptConnection();
			mutex->lock();
			cout << "Connection received!" << endl;
			mutex->unlock();
			string ip = s->getIPAddress();
			int port = s->getPortNumber();
			string id = "logger_at_" + ip + ":" + Functions::numberToString(port);
			RemoteLogger* remoteLogger = new RemoteLogger(s, id);
			remoteLogger->start();
			remoteLoggers.push_back(remoteLogger);
		}
	} catch (NetworkException& ex) {
		mutex->lock();
		cerr << "Exception catched on main() -> " << ex.what() << endl;
		mutex->unlock();
	}

	for (vector<RemoteLogger*>::iterator it = remoteLoggers.begin();
			it != remoteLoggers.end(); it++) {

		((RemoteLogger*)(*it))->stop();
		delete *it;
	}

	try {
		serverSocket->releasePort();
	} catch (...) {

	}
	if (serverSocket != NULL) {
		delete serverSocket;
	}

	if (mutex != NULL) {
		delete mutex;
	}

	return 0;
}
