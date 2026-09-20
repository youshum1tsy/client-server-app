#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <ws2tcpip.h>
#include <string>
#include <iostream>

int main() {

	WSADATA wsaData;
	std::cout << "Client\n";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Winsock init failed!" << std::endl;
		system("pause");
		return 1;
	} 

	// AF_INET: IPV4 protocol, SOCK_STREAM: TCP socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Socket creation failed! Error:" << WSAGetLastError() << std::endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	// htons(): Converts port to network byte order.
	serverAddress.sin_port = htons(8080);
	// INADDR_ANY: Accept connections on any IP.
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

	if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) {
		std::cout << "Connect failed! Error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	std::string message = "Hello, server!";
	send(clientSocket, message.c_str(), message.length(), 0);
	closesocket(clientSocket);
	WSACleanup();
	std::cout << "\nPress enter to quit...";
	std::cin.clear();
	std::cin.get();
	return 0;
}