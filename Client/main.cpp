#include <winsock2.h>
#include <string>

int main() {
	// AF_INET: IPV4 protocol, SOCK_STREAM: TCP socket
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	// htons(): Converts port to network byte order.
	serverAddress.sin_port = htons(8080);
	// INADDR_ANY: Accept connections on any IP.
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	std::string message = "Hello, server!";
	send(clientSocket, message.c_str(), message.length(), 0);
	closesocket(clientSocket);

	return 0;
}