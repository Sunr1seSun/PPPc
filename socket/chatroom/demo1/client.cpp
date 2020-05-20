#pragma warning(disable:4996)
#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include <mutex>
#pragma comment (lib, "ws2_32.lib")

using namespace std;


int generatePort()
{
	srand((unsigned)time(NULL));
	int x = 1024 + rand() % (5000 - 1024);
	return x;
}

void receiver(SOCKET recvSock, sockaddr_in clntAddr)
{
	char recv_buf[1024];
	memset(recv_buf, 0, sizeof(recv_buf));
	int clnt_length = sizeof(clntAddr);
	while (true) {
		int x = recvfrom(recvSock, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*) & clntAddr, &clnt_length);
		cout << recv_buf << endl;
	}
}

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
	int portNum = generatePort();

	// Create socket
	SOCKET sendSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sendSock == INVALID_SOCKET) {
		cerr << "Can't create send socket!" << endl;
		return 1;
	}
	SOCKET recvSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (recvSock == INVALID_SOCKET) {
		cerr << "Can't create receive socket!" << endl;
		return 1;
	}

	// server address
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(54000);
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	
	// client address
	sockaddr_in clntAddr;
	clntAddr.sin_family = AF_INET;
	clntAddr.sin_port = htons(portNum);
	clntAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	

	int opt = 1;
	setsockopt(recvSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
	int recvBin = bind(recvSock, (sockaddr*)&clntAddr, sizeof(clntAddr));
	if (recvBin == SOCKET_ERROR) cerr << "receive bind error!" << endl;

	setsockopt(sendSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
	int sendBin = bind(sendSock, (sockaddr*)&clntAddr, sizeof(clntAddr));
	if (sendBin == SOCKET_ERROR) cerr << "send bind error!" << endl;

	

	thread recv(receiver, recvSock, clntAddr);

	string userName;
	cout << "Please input your name: ";
	cin >> userName;
	
	
	
	while (true) {
		string message;
		cin >> message;
		string tempStr = userName + " : " + message + '\0';
		sendto(sendSock, (const char*)tempStr.c_str(), tempStr.length(), 0, (struct sockaddr*) & servAddr, sizeof(servAddr));
		cout << "ok" << endl;
	}

	
	
	closesocket(sendSock);
	WSACleanup();
	return 0;

}