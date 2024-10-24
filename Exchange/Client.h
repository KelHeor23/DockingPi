/*!
    \file
    \brief Класс описывающий работу клиента
    \author Князев А.И
*/
#ifndef CLIENT_H
#define CLIENT_H

#include "IExchange.h"

class Client    : public IExchange
{
public:
    Client() = delete;
    Client(std::string address, std::size_t port);
    ~Client();

    void send(std::string msg)     override;
    void read()     override;
};

#endif // CLIENT_H
