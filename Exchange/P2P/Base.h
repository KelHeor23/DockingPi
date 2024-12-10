#ifndef BASE_H
#define BASE_H

#include <mutex>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Base{
public:
    void writeMsgPapa(std::string str)
    {
        std::lock_guard<std::mutex> lock(mtxPapa);
        msgPapa = str;
    }

    std::string readMsgPapa()
    {
        std::lock_guard<std::mutex> lock(mtxPapa);
        return msgPapa;
    }

    std::string readMsgMama()
    {
        std::lock_guard<std::mutex> lock(mtxMama);
        return msgMama;
    }

    void writeMsgMama(std::string str)
    {
        std::lock_guard<std::mutex> lock(mtxMama);
        msgMama = str;
    }

    bool checkConnection(){
        return socket.is_open();
    }

public:
    boost::asio::io_service io_service;
    tcp::socket socket{io_service};

    std::string msgMama = "000";
    std::string msgPapa = "0000";
    std::mutex mtxMama;
    std::mutex mtxPapa;
};

#endif // BASE_H
