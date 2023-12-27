#include "ChatServer.h"

void Server::makeAddr(string ip, int port)
{
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
	server_addr.sin_port = htons(port);
}

void Server::initSocket()
{
	if (WSAStartup(MAKEWORD(2, 2), &this->wsadata) != 0) {
		elog("WSAstartup failed");
	}
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
}

Server::Server(string ip, int port)
{
	initSocket();
	makeAddr(ip, port);
	
	if (bind(server_socket, getAddr(), sizeof(server_addr)) == -1) {
		elog("bind fail");
		this->~Server();
		return;
	}

	listen(server_socket, 20);

	open = true;
}


void Server::sendMsgToAllButNotSelf(int socket_fd)
{

}

SOCKADDR * Server::getAddr()
{
	return (SOCKADDR*)&server_addr;
}


SOCKET Server::getSocketFD()
{
	return server_socket;
}


void Server::addClientSocketFD(SOCKET socket_fd)
{
	client_sockets.push_back(socket_fd);
}

bool Server::isOpen()
{
	return open;
}


void Server::removeSocketFD(SOCKET client_socket)
{
	/*for (auto it = client_sockets.begin(); it != client_sockets.end(); it++) {
		if (*it == client_socket) {
			client_sockets.erase(it);
			return;
		}
	}*/
	auto it = std::find(client_sockets.begin(), client_sockets.end(), client_socket);
	if (it != client_sockets.end()) {
		client_sockets.erase(it);
	}
}

vector<int> Server::getClientFDs()
{
	return client_sockets;
}

Server::~Server()
{

	for (SOCKET s : client_sockets) 
		closesocket(s);

	closesocket(server_socket);
	WSACleanup();
}

