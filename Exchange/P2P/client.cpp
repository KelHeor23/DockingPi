#include "client.h"

#include <iostream>
#include <thread>

#include "../../config.h"

using boost::asio::ip::tcp;

Client::Client() {

}

void Client::exchange()
{
    if (!checkConnection()){
        static bool conRefFirst = true;
        boost::system::error_code error;

        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(address_g), port_g), error);

        if (error && conRefFirst) {
            std::cout << "Connection refuse. Try to connect..." << std::endl;
            conRefFirst = false;
        } else if (!error){
            std::cout << "Connection complite!" << std::endl;
        }
    } else {
        if (socket.is_open()) {
            boost::system::error_code write_error;
            boost::asio::write(socket, boost::asio::buffer(readMsgPapa() + "\n"), write_error);

            if (write_error) {
                std::cerr << "Error when I try to send msg: " << write_error.message() << std::endl;
                return;
            }

            boost::asio::streambuf buf;
            boost::asio::read_until(socket, buf, '\n', write_error);
            if (write_error) {
                std::cerr << "Error when I try to read msg: " << write_error.message() << std::endl;
                return;
            }

            std::istream input_stream(&buf);
            std::string message;
            std::getline(input_stream, message);

            writeMsgMama(message);
            // Обработка принятого сообщения
            std::cout << "Received: " << message << std::endl;
        } else {
            std::cerr << "Connection refuse. Try to connect..." << std::endl;
        }
    }
}
