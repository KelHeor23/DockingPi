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

    void send(std::string msg)     override;
    void read()     override;
};

#endif // SERVER_H
