/*!
    \file
    \brief Класс описывающий работу клиента
    \author Князев А.И
*/
#ifndef CLIENT_H
#define CLIENT_H

#include "IExchange.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

class Client    : public IExchange
{
public:
    Client();
    ~Client();

    void sendMsg(std::string msg)   override;
    std::string read()              override;
    bool connect(std::string address, std::size_t port) override;

private:
    int clientSocket = 0;
    struct sockaddr_in serverAddr;
    size_t bufferSize = 16;
};

#endif // CLIENT_H
