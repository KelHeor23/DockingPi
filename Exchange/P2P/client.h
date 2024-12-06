#ifndef CLIENT_H
#define CLIENT_H

#include <mutex>
#include <string>
class Client
{
public:
    Client();

    std::string readMsgMama();
    void writeMsgPapa(std::string str);

private:
    void client_to_server_exchange();

    std::string msgMama;
    std::string msgPapa;
    std::mutex mtxMama;
    std::mutex mtxPapa;
};

#endif // CLIENT_H
