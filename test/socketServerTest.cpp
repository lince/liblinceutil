#include <string>
#include <iostream>
using namespace std;

#include "../include/network/ServerSocketTCP.h"
#include "../include/network/SocketTCP.h"
#include "../include/Functions.h"
using namespace cpputil::network;

int main(int argc, char* argv[]) {
	ServerSocketTCP* serverSocket = new ServerSocketTCP(12345);
	serverSocket->bindPort();
	serverSocket->startListen();
	SocketTCP* s = serverSocket->acceptConnection();

	for (int i = 0; i < 255; i++) {
		DataPayload* data = s->receiveData();
		cout << "Data Received from ["
				<< s->getIPAddress() << ":" << s->getPortNumber()
				<< "]: " << data->getDataAsString() << endl;
		delete data;

		string message = "\"Message to client ";
		message += cpputil::Functions::numberToString(i);
		message += ".\"";
		data = new DataPayload(message);

		s->sendData(data);
		delete data;
	}

	s->closeConnection();
	delete s;
	serverSocket->releasePort();
	delete serverSocket;

	return 0;
}
