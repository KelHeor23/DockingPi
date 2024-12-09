#include "server.h"
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

Server::Server() {
    exchange();
}

std::string Server::readMsgPapa()
{
    std::lock_guard<std::mutex> lock(mtxPapa);
    return msgPapa;
}

void Server::writeMsgMama(std::string str)
{
    std::lock_guard<std::mutex> lock(mtxMama);
    msgMama = str;
}

void Server::exchange()
{
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

    while (true)
    {
        tcp::socket socket(io_service);

        // Ожидание подключения клиента
        acceptor.accept(socket);

        std::thread t([this, &socket](){
            while (true)
            {
                boost::asio::streambuf buf;
                boost::system::error_code error;

                // Принятие сообщения от клиента
                size_t len = boost::asio::read_until(socket, buf, '\n', error);

                if (error == boost::asio::error::eof){
                    std::cout << "Client disconnected. Waiting for new connection..." << std::endl;
                    break;
                }
                else if (error){
                    std::cerr << "Error receiving message: " << error.message() << std::endl;
                    break;
                }
                std::istream input_stream(&buf);
                mtxPapa.lock();
                std::getline(input_stream, msgPapa);
                mtxPapa.unlock();
                // Отправка сообщения клиенту

                mtxMama.lock();
                boost::asio::write(socket, boost::asio::buffer(msgMama + "\n"));
                mtxMama.unlock();
            }
        });
        t.detach(); // Запуск обмена сообщениями в отдельном потоке
    }
}
