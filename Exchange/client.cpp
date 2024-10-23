#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Создание сокета
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Настройка адреса сервера
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000); // Порт сервера
    serverAddr.sin_addr.s_addr = inet_addr("10.42.0.1");

    // Подключение к серверу
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Отправка сообщения серверу
    send(clientSocket, "Привет", sizeof("Привет"), 0);

    // Получение ответного сообщения от сервера
    char buffer[256];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Ответ от сервера: " << buffer << std::endl;

    // Закрытие сокета
    close(clientSocket);

    return 0;
}
