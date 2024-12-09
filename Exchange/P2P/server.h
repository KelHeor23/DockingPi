#ifndef SERVER_H
#define SERVER_H

#include "Base.h"

class Server : public Base
{
public:
    Server();

    std::string readMsgPapa();
    void writeMsgMama(std::string str);

private:
    void exchange();
};

#endif // SERVER_H
