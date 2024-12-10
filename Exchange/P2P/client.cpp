#include "client.h"

#include <iostream>
#include <thread>

#include "../../config.h"

using boost::asio::ip::tcp;

Client::Client() {

}

void Client::exchange()
{
    if (checkConnection()){
        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(address_g), port_g));
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Отправка сообщения
        boost::asio::write(socket, boost::asio::buffer(readMsgPapa() + "\n"));

        // Принятие сообщения
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, '\n');
        std::istream input_stream(&buf);
        std::string message;
        std::getline(input_stream, message);

        writeMsgMama(message);
        // Обработка принятого сообщения
        std::cout << "Received: " << message << std::endl;
    }
}
