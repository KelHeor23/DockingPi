#ifndef CLIENT_H
#define CLIENT_H

#include "Base.h"

class Client : public Base
{
public:
    Client();

    std::string readMsgMama();
    void writeMsgPapa(std::string str);

private:
    void client_to_server_exchange();
};

#endif // CLIENT_H
