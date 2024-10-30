#include "Server.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

Server::Server() : serverSocket(0), clientSocket(0), bufferSize(1024) {
}

Server::~Server() {
    if (clientSocket != 0) {
        close(clientSocket);
    }
    if (serverSocket != 0) {
        close(serverSocket);
    }
}

void Server::sendMsg(std::string msg) {
    if (send(clientSocket, msg.c_str(), msg.size(), 0) == -1) {
        std::cerr << "Error sending message: " << strerror(errno) << std::endl;
    }
}

std::string Server::read() {
    std::string buffer(bufferSize, 0);
    ssize_t bytesRead = ::read(clientSocket, &buffer[0], bufferSize);
    if (bytesRead == -1) {
        std::cerr << "Error reading from client: " << strerror(errno) << std::endl;
        return "";
    }
    return buffer.substr(0, bytesRead);
}

bool Server::connect(std::string address, std::size_t port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket: " << strerror(errno) << std::endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(address.c_str());

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding server socket to server address: " << strerror(errno) << std::endl;
        return false;
    }

    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening for incoming connections: " << strerror(errno) << std::endl;
        return false;
    }

    socklen_t addrlen = sizeof(serverAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&serverAddr, &addrlen);
    if (clientSocket == -1) {
        std::cerr << "Error creating client socket in server: " << strerror(errno) << std::endl;
        return false;
    }

    return true;
}
