#include <iostream>
#include <unistd.h>

#include "Servo/Servo_SPT5535LV360.h"
#include "Servo/Servo_DS3235_270.h"

int main()
{
    std::cout << "docking begin" << std::endl;

    if (wiringPiSetup() == -1) {
        std::cerr << "Ошибка инициализации WiringPi." << std::endl;
        return 1;
    }

    Servo_DS3235_270 servo1(7);

    while (true) {
        servo1.writePWM(Servo_DS3235_270::CV1);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CV2);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CV3);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CV4);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CV5);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CV6);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CV7);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CV8);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CV9);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CV10);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV1);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV2);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV3);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV4);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV5);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV6);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV7);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV8);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV9);
        usleep(500000); // Подождать 0.5 секунды
        servo1.writePWM(Servo_DS3235_270::CCV10);
        usleep(500000); // Подождать 0.5 секунды
    }

    return 0 ;
}
