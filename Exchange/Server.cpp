#include "Server.h"

Server::Server(){
}

Server::~Server()
{
    close(clientSocket);
    close(serverSocket);
}

void Server::sendMsg(std::string msg)
{
    send(clientSocket, msg.c_str(), msg.size(), 0);
}

std::string Server::read()
{
    std::string buffer;
    buffer.resize(bufferSize);
    ::read(clientSocket, buffer.data(), bufferSize);
    return buffer;
}

bool Server::connect(std::string address, std::size_t port)
{
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        throw("Error creating server socket");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(address.c_str());

    if ((bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) == 0){
        throw("Error binding server socket to server adress");
    }

    std::size_t cntTrying = 5;
    if ((listen(serverSocket, cntTrying)) < 0) {
        throw("Error. " + std::to_string(cntTrying) + " linstening attempts is falls");
    }

    socklen_t addrlen = sizeof(serverAddr);
    if ((clientSocket = accept(serverSocket, (struct sockaddr*)&serverAddr, (socklen_t*)&addrlen)) < 0){
        throw("Error creating client socket in server");
    }

    return true;
}
