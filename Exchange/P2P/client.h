#ifndef CLIENT_H
#define CLIENT_H

#include "Base.h"

class Client : public Base
{
public:
    Client();

    void exchange();

private:
    bool isConnect = false;
};

#endif // CLIENT_H
