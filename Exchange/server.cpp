#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Создание сокета
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Настройка адреса сервера
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345); // Порт для прослушивания

    // Привязка сокета к адресу и порту
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Прослушивание входящих соединений
    listen(serverSocket, 5);

    // Принятие входящего соединения от клиента
    int clientSocket = accept(serverSocket, NULL, NULL);

    // Получение сообщения от клиента
    char buffer[256];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Сообщение от клиента: " << buffer << std::endl;

    // Отправка сообщения обратно клиенту
    send(clientSocket, "Привет", sizeof("Привет"), 0);

    // Закрытие сокетов
    close(clientSocket);
    close(serverSocket);

    return 0;
}
