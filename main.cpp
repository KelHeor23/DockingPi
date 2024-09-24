#include <iostream>
#include <thread>
#include <unistd.h>

#include "Docker/DockerFactory.h"
#include "Mavlink/MavlinkExchange.h"


// Execution frequency
void exec_freq(){
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

int main(int argc, char *argv[])
{
    DockerFactory factory;
    std::unique_ptr<Docker> docker;

    MavlinkExchange mavExchange;
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

    if (!mavExchange.init())
        return 0;

    std::cout << "Docking begin" << std::endl;

    while (true) {
        if (mavExchange.getStartPin())
            docker->docking();
        else
            docker->undocking();
        exec_freq();
    }
    return 0;
}
