#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "../Util/Log.h"

#pragma comment(lib,"Ws2_32.lib")
using namespace std;

class Server {
	WSADATA wsadata;

	SOCKET server_socket;
	sockaddr_in server_addr;

	vector<int> client_sockets;

	bool open = false;

	void makeAddr(string ip, int port);
	void initSocket();
public:
	Server(string ip, int port);
	~Server();
	
	void sendMsgToAllButNotSelf(int socket_fd);
	SOCKADDR* getAddr();
	SOCKET getSocketFD();
	void addClientSocketFD(SOCKET socket_fd);
	bool isOpen();
	void removeSocketFD(SOCKET client_socket);
	vector<int> getClientFDs();
};