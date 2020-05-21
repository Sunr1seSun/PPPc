#pragma warning(disable:4996);
#include <iostream>
#include <WS2tcpip.h>
#include <map>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

#define BUFFER_LENGTH 1024
#define DEFAULT_PORT 54000

class server
{
public:
	bool Startup();
	bool CreateSocket();
	bool BindSocket();
	void Work();
	void SendMessage(string message, sockaddr_in x);
private:
	WSADATA wsData;
	SOCKET listening;
	sockaddr_in ser;	//服务器地址
	sockaddr_in cli;	//客户地址
	char recv_buf[BUFFER_LENGTH];
	map<string, sockaddr_in> userTable;
};

bool server::Startup()
{
	WORD ver = MAKEWORD(2, 2);
	if (WSAStartup(ver, &wsData) != 0) {
		cerr << "Can't Intialize winsock!" << endl;
		return false;
	}
	return true;
}

bool server::CreateSocket()
{
	listening = socket(AF_INET, SOCK_DGRAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket!" << endl;
		return false;
	}
	return true;
}

bool server::BindSocket()
{
	ser.sin_family = AF_INET;
	ser.sin_port = htons(DEFAULT_PORT);
	ser.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(listening, (sockaddr*)&ser, sizeof(ser)) == SOCKET_ERROR) {
		cerr << "bind error!" << endl;
		return false;
	}
	return true;
}

void server::SendMessage(string message, sockaddr_in x)
{
	char* send_buf = new char[message.length() + 1];
	strcpy(send_buf, message.c_str());
	SOCKET rSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (rSocket == INVALID_SOCKET) {
		cerr << "Can't create a socket!" << endl;
		return;
	}
	cout << "send message : (" << message << ") to " << x.sin_port << endl;
	int iSend = sendto(rSocket, send_buf, message.length() + 1, 0, (SOCKADDR*)&x, sizeof(x));
	if (iSend == SOCKET_ERROR)
	{
		cout << "sendto failed:" << WSAGetLastError() << endl;
		closesocket(rSocket);
		return;
	}
	closesocket(rSocket);
}

void server::Work()
{
	int nSize = sizeof(sockaddr_in);
	while (true) {
		memset(recv_buf, 0, sizeof(recv_buf));
		recvfrom(listening, recv_buf, BUFFER_LENGTH, 0, (sockaddr*)&cli, &nSize);
		string recv_message(recv_buf);
		cout << "receive message (" << recv_message << ") from " << cli.sin_port << endl;
		if(recv_message.find(':') == recv_message.npos)
			userTable[recv_message] = cli;
		else {
			// 将收到的信息转发给各用户
			for (auto x : userTable) {
				if (x.second.sin_port == cli.sin_port)
					continue;
				SendMessage(recv_message, x.second);
			}
		}	
	}
	closesocket(listening);
}

int main()
{
	server s;
	// Initialze winsock
	if(s.Startup() == false) return 0;
	
	// Create a socket
	if (s.CreateSocket() == false) return 0;

	// Bind an ip address and port to a socket
	if (s.BindSocket() == false) return 0;

	s.Work();

	WSACleanup();
	return 0;
}