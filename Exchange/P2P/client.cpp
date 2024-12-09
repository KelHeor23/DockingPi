#include <iostream>
#include <boost/asio.hpp>
#include <thread>

#include "../../config.h"

#include "client.h"

using boost::asio::ip::tcp;

Client::Client() {
    exchange();
}

std::string Client::readMsgMama()
{
    std::lock_guard<std::mutex> lock(mtxMama);
    return msgMama;
}

void Client::writeMsgPapa(std::string str)
{
    std::lock_guard<std::mutex> lock(mtxPapa);
    msgPapa = str;
}

void Client::exchange()
{
    // Инициализация io_service
    boost::asio::io_service io_service;
    // Установка соединения
    tcp::socket socket(io_service);

    bool connected = false;
    while (!connected)
    {
        try
        {
            tcp::endpoint endpoint(boost::asio::ip::address::from_string(address_g), port_g);
            socket.connect(endpoint);
            connected = true;
        }
        catch (std::exception& e)
        {
            std::cerr << "Connection failed, retrying... " << e.what() << std::endl;
            // Пауза перед следующей попыткой подключения
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::thread t([this, &socket]() {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            mtxPapa.lock();
            // Отправка сообщения
            boost::asio::write(socket, boost::asio::buffer(msgPapa + "\n"));
            mtxPapa.unlock();

            // Принятие сообщения
            boost::asio::streambuf buf;
            boost::asio::read_until(socket, buf, '\n');
            std::istream input_stream(&buf);

            mtxMama.lock();
            std::getline(input_stream, msgMama);
            // Обработка принятого сообщения
            std::cout << "Received: " << msgMama << std::endl;
            mtxMama.unlock();
        }
    });
    t.detach();
}
