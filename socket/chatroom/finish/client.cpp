#pragma warning(disable:4996)
#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include <string>
#include <mutex>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

#define BUFFER_LENGTH 1024
#define DEFAULT_PORT 54000

class client
{
public:
	void GeneratePort();
	bool Startup();
	bool CreateSocket();
	bool BindSocket();
	void Receive();
	void Send();


private:
	WSADATA wsData;
	SOCKET sendSock, recvSock;
	sockaddr_in servAddr, clntAddr;
	int portNum;
	char recv_buf[BUFFER_LENGTH];
	string userName;
};

void client::GeneratePort()
{
	srand((unsigned)time(NULL));
	portNum = 1024 + rand() % (5000 - 1024);
}

bool client::Startup()
{
	WORD ver = MAKEWORD(2, 2);
	if (WSAStartup(ver, &wsData) != 0) {
		cerr << "Can't Intialize winsock!" << endl;
		return false;
	}
	return true;
}

bool client::CreateSocket()
{
	sendSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sendSock == INVALID_SOCKET) {
		cerr << "Can't create send socket!" << endl;
		return false;
	}
	recvSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (recvSock == INVALID_SOCKET) {
		cerr << "Can't create receive socket!" << endl;
		return false;
	}
	return true;
}

bool client::BindSocket()
{
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(DEFAULT_PORT);
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	clntAddr.sin_family = AF_INET;
	clntAddr.sin_port = htons(portNum);
	clntAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int opt = 1;
	setsockopt(recvSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
	int recvBin = bind(recvSock, (sockaddr*)&clntAddr, sizeof(clntAddr));
	if (recvBin == SOCKET_ERROR) {
		cerr << "receive bind error!" << endl;
		return false;
	} 

	setsockopt(sendSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
	int sendBin = bind(sendSock, (sockaddr*)&clntAddr, sizeof(clntAddr));
	if (sendBin == SOCKET_ERROR) {
		cerr << "send bind error!" << endl;
		return false;
	} 
	return true;
}

void client::Receive()
{
	int clnt_length = sizeof(clntAddr);
	while (true) {
		memset(recv_buf, 0, sizeof(recv_buf));
		int x = recvfrom(recvSock, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*) & clntAddr, &clnt_length);
		cout << recv_buf << endl;
	}
	closesocket(recvSock);
}

void client::Send()
{
	cout << "Please input your name: ";
	getline(cin, userName);
	sendto(sendSock, (const char*)userName.c_str(), userName.length(), 0, (struct sockaddr*) & servAddr, sizeof(servAddr));
	while (true) {
		string message;
		getline(cin, message);
		string tempStr = userName + " : " + message + '\0';
		sendto(sendSock, (const char*)tempStr.c_str(), tempStr.length(), 0, (struct sockaddr*) & servAddr, sizeof(servAddr));
		cout << tempStr << endl;
	}
	closesocket(sendSock);
}

int main()
{
	client c;
	// Initialze winsock
	if (c.Startup() == false) return 0;
	c.GeneratePort();

	// Create socket
	if (c.CreateSocket() == false) return 0;

	if (c.BindSocket() == false) return 0;

	thread recv(&client::Receive, c);

	c.Send();

	WSACleanup();
	return 0;

}