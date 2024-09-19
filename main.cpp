#include <iostream>
#include <unistd.h>

#include "Servo/Servo.h"

int main()
{
    std::cout << "docking begin" << std::endl;

    if (wiringPiSetup() == -1) {
        std::cerr << "Ошибка инициализации WiringPi." << std::endl;
        return 1;
    }

    return 0 ;
}
