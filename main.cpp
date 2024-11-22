/*!
    \file
    \brief Базовый файл main.
    \author Князев А.И
*/

#include <iostream>
#include <thread>
#include <unistd.h>

#include <ncurses.h>
#include <wiringPi.h>

#include "Docker/DockerFactory.h"
#include "Mavlink/MavlinkExchange.h"

#define JOYSTICK 1 ///< Макрос указывающий что запуск производится с ипользованием джостика

/*!
    Функция задающая задержку в миллисекундах для каждой иттерации работы docking
*/
void exec_freq(){
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

/*!
    \brief  Для запуска программы ожидается передача первым аргументом указания для какого устрйоства будет она скомпилирована (Mama или Papa).
    \param[in] argc количество аргументов командной строки, переданных программе, включая название самой программы.
    \param[in] pin  представляет собой массив строк (char*), 0 аргумент - имя программы, 1 - режим запуска (Mama или Papa)
    \return Код завершения программы.
*/
int main(int argc, char *argv[])
{
    DockerFactory factory;          ///> factory - Фабрика модулей стыковки
    std::unique_ptr<Docker> docker; ///> docker - Непосредсвтенный механизм стыковки

    /* Read params and running fabric*/
    //-----------------------------------------------------------------------------------------------

    {
        if (argc != 2) {
            std::cerr << "Please write type of drone. Types: " << types_g << std::endl;
            return 0;
        }

        if (wiringPiSetup() == -1) {
            std::cerr << "Ошибка инициализации WiringPi." << std::endl;
            return 0;
        }

        std::string type(argv[1]);

        if (type.compare("Papa") == 0){
            docker = factory.makeDocker(Dockers::Papa);
        } else if (type.compare("Mama") == 0){
            docker = factory.makeDocker(Dockers::Mama);
        } else {
            std::cerr << "unknow type of drone. Types: " << types_g << std::endl;
            return 0;
        }

        std::cout << "The program is running for type" << type << std::endl;
    }
    //-----------------------------------------------------------------------------------------------

    //
    /*
    try {
        docker->connect();
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }*/

#if JOYSTICK
    MavlinkExchange mavExchange;
    if (!mavExchange.init())
        return 0;

    std::cout << "Docking begin" << std::endl;

    while (true) {
        switch(mavExchange.getStartPin()){
        case 1:
            docker->docking();
            break;
        case 0:
            docker->undocking();
            break;
        default:
            docker->stop();
            break;

        }
        exec_freq();
    }
#else
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // Устанавливаем неблокирующий режим ввода
    int key, temp;
    bool first = true;
    while (true) {
        key = getch();
        if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5')
            temp = key;

        switch (temp) {
        case '1':
            docker->docking();
            first = true;
            break;
        case '2':
            docker->undocking();
            first = true;
            break;
        case '3':
            docker->cargoLock();
            docker->stop();
            if (first){
                std::cout << "Current pos: " << docker->odometerCargo.getCurPos() << std::endl;
                first = false;
            }
            break;
        case '4':
            docker->cargoCV();
            first = true;
            break;
        case '5':
            docker->cargoCCV();
            first = true;
            break;
        } 
    }

    endwin();
#endif

    return 0;
}
