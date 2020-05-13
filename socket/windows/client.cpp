#include <iostream>
#include <WS2tcpip.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main()
{
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	
	int wsOK = WSAStartup(ver, &wsData);
	if (wsOK != 0)
	{
		cerr << "Can't Intialize winsock!" << endl;
		return 1;
	}

	// Create a socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket != INVALID_SOCKET) {
		cerr << "Can't create a socket!" << endl;
	}

	// Bind an ip address and port to a socket
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(54000);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	// connect
	if (connect(clientSocket, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
		cerr << "connect error!" << endl;
		return 1;
	}

	cout << "Connected!" << endl;
	char sendBuf[4096];
	char recvBuf[4096];
	while (true) {
		ZeroMemory(sendBuf, 4096);
		ZeroMemory(recvBuf, 4096);
		cout << "Please input your message to server:";
		cin >> sendBuf;
		send(clientSocket, sendBuf, sizeof(sendBuf), 0);
		recv(clientSocket, recvBuf, sizeof(recvBuf), 0);
		cout << "receive a message from server:"<< recvBuf << endl;
	}
	closesocket(clientSocket);

	WSACleanup();

}
