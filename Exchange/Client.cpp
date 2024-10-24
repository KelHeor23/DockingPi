#include "Client.h"

Client::Client(std::string address, std::size_t port) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(address.c_str());

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
}

Client::~Client()
{
    close(clientSocket);
}

void Client::sendMsg(std::string msg)
{
    send(clientSocket, msg.c_str(), msg.size(), 0);
}

std::string Client::read()
{
    char buffer[16];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    return std::string(buffer);
}
