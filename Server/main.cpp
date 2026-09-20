#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <string>
#include <iostream>

int main() {
	WSADATA wsaData;
	std::cout << "Server\n";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Winsock init failed!" << std::endl;
		system("pause");
		return 1;
	}

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Socket creation failed! Error:" << WSAGetLastError() << std::endl;
		WSACleanup();
		system("pause");
		return 1;
	}
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) {
		std::cout << "Bind failed! Error: " << WSAGetLastError() << std::endl;
		system("pause");
		return 1;
	}

	if (listen(serverSocket, 5)) {
		std::cout << "Listen failed! Error: " << WSAGetLastError() << std::endl;
		system("pause");
		return 1;
	}
	SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Accept failed! Error: " << WSAGetLastError() << std::endl;
		system("pause");
		return 1;
	}

	char buffer[1024] = {0};
	int bytesRecieved = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
	if (bytesRecieved > 0) {
		std::string message(buffer);
		std::cout << "Message from client: " << message << std::endl;
	}
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	std::cout << "\nPress enter to quit...";
	std::cin.clear();
	std::cin.get();
	return 0;
}