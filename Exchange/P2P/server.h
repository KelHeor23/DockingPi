#ifndef SERVER_H
#define SERVER_H

#include "Base.h"

class Server : public Base
{
public:
    Server();

    void exchange();

private:
    tcp::acceptor acceptor;
};

#endif // SERVER_H
