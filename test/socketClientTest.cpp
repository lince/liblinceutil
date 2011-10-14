#include <string>
#include <iostream>
using namespace std;

#include "../include/network/SocketTCP.h"
#include "../include/Functions.h"
using namespace cpputil::network;

int main(int argc, char* argv[]) {
	SocketTCP* s = new SocketTCP("127.0.0.1", 12345);
	s->connectSocket();

	for (int i = 0; i < 255; i++) {
		string message = "\"Message to server ";
		message += cpputil::Functions::numberToString(i);
		message += ".\"";
		DataPayload* data = new DataPayload(message);

		s->sendData(data);
		delete data;

		data = s->receiveData();
		cout << "Data Received from ["
			<< s->getIPAddress() << ":" << s->getPortNumber()
			<< "]: " << data->getDataAsString() << endl;
		delete data;
	}

	s->closeConnection();
	delete s;

	return 0;
}
