#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOK = WSAStartup(ver, &wsData);
	if (wsOK != 0) {
		cerr << "Can't Intialize winsock!" << endl;
		return 1;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_DGRAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket!" << endl;
		return 1;
	}

	// Bind an ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// listening
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	char buffer[100];
	while (true) {
		cout << "1" << endl;
		recvfrom(listening, buffer, 100, 0, &clntAddr, &nSize);
		cout << buffer << endl;
	}

	closesocket(listening);
	WSACleanup();
	return 0;
}