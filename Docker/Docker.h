#ifndef DOCKER_H
#define DOCKER_H

#include "../Servo/Servo.h"

#include "DockerPinout.h"
#include <string>

class Docker {
public:
    Docker() : servoRod(PIN_ROD), servoCargo(PIN_CARGO),
        servoRightHook(PIN_RIGHT_HOOK), servoLeftHook(PIN_LEFT_HOOK) {}

    virtual ~Docker(){}

    virtual void docking()      = 0;
    virtual void undocking()    = 0;
    virtual void stop()         = 0;

public:
    Servo_SPT5535LV360  servoRod;       // Серва штанги
    Servo_SPT5535LV360  servoCargo;     // Серва телеги
    Servo_DS3235_270    servoRightHook; // Серва правого крюка
    Servo_DS3235_270    servoLeftHook;  // Серва левого крюка

public:
    /*
    MSG_mama
    0 - готовность
    1 - хуки закрылись
    2 - телега пришла к маме
    */
    std::string MSG_mama = "000";          // Сообщение отправленное от мамы

    /*
    MSG_papa
    0 - готовность
    1 - стрела выдвинулась
    2 - дроны стянулись
    3 - телега покинула папу
    */
    std::string MSG_papa = "0000";         // Сообщение отправленное от папы
};

#endif // DOCKER_H
