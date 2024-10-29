#include "Client.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

Client::Client() : clientSocket(0), bufferSize(1024) {
}

Client::~Client() {
    if (clientSocket != 0) {
        close(clientSocket);
    }
}

void Client::sendMsg(std::string msg) {
    if (send(clientSocket, msg.c_str(), msg.size(), 0) == -1) {
        std::cerr << "Error sending message: " << strerror(errno) << std::endl;
    }
}

std::string Client::read() {
    std::string buffer(bufferSize, 0);
    ssize_t bytesRead = ::read(clientSocket, &buffer[0], bufferSize);
    if (bytesRead == -1) {
        std::cerr << "Error reading from server: " << strerror(errno) << std::endl;
        return "";
    }
    return buffer.substr(0, bytesRead);
}

bool Client::connect(std::string address, std::size_t port) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating client socket: " << strerror(errno) << std::endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(address.c_str());

    if (::connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting client socket to server: " << strerror(errno) << std::endl;
        return false;
    }

    return true;
}
