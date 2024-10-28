/*!
    \file
    \brief Класс описывающий работу сервера
    \author Князев А.И
*/
#ifndef SERVER_H
#define SERVER_H

#include "IExchange.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

class Server : public IExchange
{
public:
    Server();
    ~Server();

    void sendMsg(std::string msg)   override;
    std::string read()              override;
    bool connect(std::string address, std::size_t port) override;

private:
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr;
    size_t bufferSize = 16;
};

#endif // SERVER_H
