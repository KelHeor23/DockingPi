#include <iostream>
#include <unistd.h>

#include "Servo/Servo_SPT5535LV360.h"

int main()
{

    std::cout << "docking begin" << std::endl;

    if (wiringPiSetup() == -1) {
        std::cerr << "Ошибка инициализации WiringPi." << std::endl;
        return 1;
    }

    Servo_SPT5535LV360 servo1(7);

    while (true) {
        servo1.writePWM(PWM::CV10);
        usleep(1500000); // Подождать 0.5 секунды

        servo1.writePWM(PWM::CCV10);
        usleep(1500000); // Подождать 0.5 секунды

        servo1.writePWM(PWM::STOP);
        usleep(1500000); // Подождать 0.5 секунды
    }

    return 0 ;
}
