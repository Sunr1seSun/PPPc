#pragma warning(disable:4996);
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
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create a socket!" << endl;
		return 1;
	}

	// server address
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(54000);
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	string userName;
	cout << "Please input your name: ";
	cin >> userName;
	while (true) {
		string message;
		cin >> message;
		string tempStr = userName + " : " + message + '\0';
		sendto(sock, (const char*)tempStr.c_str(), tempStr.length(), 0, (struct sockaddr*) & servAddr, sizeof(servAddr));
		cout << "ok" << endl;
	}
	
	closesocket(sock);
	WSACleanup();
	return 0;

}