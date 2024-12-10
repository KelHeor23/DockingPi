#include "server.h"

#include <iostream>

#include "../../config.h"

Server::Server() : acceptor(io_service, tcp::endpoint(tcp::v4(), port_g)) {
    acceptor.accept(socket);
}

void Server::exchange()
{
    // Принятие сообщения
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, '\n');
    std::istream input_stream(&buf);
    std::string message;
    std::getline(input_stream, message);
    writeMsgPapa(message);

    // Обработка принятого сообщения
    std::cout << "Received: " << message << std::endl;

    // Отправка сообщения
    boost::asio::write(socket, boost::asio::buffer(readMsgMama() + "\n"));
}
