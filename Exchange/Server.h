/*!
    \file
    \brief Класс описывающий работу сервера
    \author Князев А.И
*/
#ifndef SERVER_H
#define SERVER_H

#include "IExchange.h"
class Server : public IExchange
{
public:
    Server() = delete;
    Server(std::string address, std::size_t port);
    ~Server();

    void sendMsg(std::string msg)  override;
    std::string read()          override;
};

#endif // SERVER_H
