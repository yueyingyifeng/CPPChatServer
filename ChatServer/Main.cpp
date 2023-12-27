#include <sstream>

#include "Net/ChatServer.h"
#include "IO/ConfigManager.h"
#include "Entity/User.h"

int main() {
	ConfigManager* manager = new ConfigManager();
	ConfigFile* file = manager->getConfigFile();
	

	Server server(file->getValue(file->IP_), stoi(file->getValue(file->PORT_)));
	mutex mutex_sockets;

	
		log("Server started");
		while (server.isOpen()) {
			sockaddr_in client_addr{};
			socklen_t client_sk_len = sizeof(client_addr);
			SOCKET client_socket = accept(server.getSocketFD(), (sockaddr*)&client_addr, &client_sk_len);
			if (client_socket == -1) {
				elog("accept failed");
				continue;
			}

			{
				lock_guard<mutex> lock(mutex_sockets);
				server.addClientSocketFD(client_socket);
			}
			char ipString[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(client_addr.sin_addr), ipString, INET_ADDRSTRLEN);
			log(string("New user joined, IP: ") + ipString);

			thread([=,&server]() {
				User user;
				string passwd;
				char* buffer = new char[0xffff];
				int b_size = recv(client_socket, buffer, 0xffff, 0);
				buffer[b_size] = '\0';
				istringstream iss(buffer);

				iss >> user.username >> passwd;
				//-------验证密码
				if (file->getValue(file->PASSWD_).compare(passwd) != 0) {
					const char* wrong = "0";
					send(client_socket, wrong, strlen(wrong), 0);
					server.removeSocketFD(client_socket);
					closesocket(client_socket);
					return;
				}
				//-------
				//-------发送服务器名字
				string info = file->getValue(ConfigFile::NAME_);
				send(client_socket, info.c_str(), info.size(), 0);
				//-------
				//-------广播加入消息
				string joinMsg = user.username + " join the" + file->getValue(ConfigFile::NAME_);
				for (SOCKET s : server.getClientFDs()) {
					if (s != client_socket)
						send(s, joinMsg.c_str(), joinMsg.size(), 0);
				}
				//--------
				while (true) {
					buffer = new char[0xffff];
					b_size = recv(client_socket, buffer, 0xffff, 0);
					//-------广播离开消息
					if (b_size == -1) {
						string leaveMsg = user.username + " is leave";
						for (SOCKET s : server.getClientFDs()) {
							if (s != client_socket)
								send(s, leaveMsg.c_str(), leaveMsg.size(), 0);
						}
						break;
					}
					//-------
					buffer[b_size] = '\0';
					//-------广播消息
					string m = buffer + string(" <") + user.username;
					for (SOCKET s : server.getClientFDs()) {
						if (s != client_socket)
							send(s, m.c_str(), m.size(), 0);
					}
					//-------
				}
				delete buffer;
				buffer = nullptr;
			}).detach();

		}//server.isOpen()
		server.~Server();
	return 0;
}