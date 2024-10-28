#include "Client.h"

Client::Client()
{

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
    std::string buffer;
    buffer.resize(bufferSize);
    ::read(clientSocket, buffer.data(), bufferSize);
    return buffer;
}

bool Client::connect(std::string address, std::size_t port)
{
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        throw("Error creating client socket");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(address.c_str());

    if (::connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0){
        throw("Error connect client socket to server");
    }
}
