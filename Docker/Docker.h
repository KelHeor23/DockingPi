#ifndef DOCKER_H
#define DOCKER_H

#include <chrono>
#include <string>

#include "../Servo/Servo.h"
#include "DockerPinout.h"

using m_time = std::chrono::system_clock;

class Docker {
public:
    Docker() : servoRod(PIN_ROD), servoCargo(PIN_CARGO),
        servoRightHook(PIN_RIGHT_HOOK), servoLeftHook(PIN_LEFT_HOOK) {
        pinMode(PIN_ROD_EXTENTION, INPUT);
        pinMode(PIN_ROD_RETRACTED, INPUT);
        pinMode(PIN_DOCKING_COMPL, INPUT);
    }

    virtual ~Docker(){}

    virtual void docking()      = 0;
    virtual void undocking()    = 0;
    virtual void stop()         = 0;

    void cargoCV(){
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CV2);
    }
    
    void cargoCCV(){
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CCV3);
    }

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

    std::chrono::time_point<m_time> lastSwitchTime = m_time::now(); // Метка времени

    int cargoAcceleration = 300;            // Промежуток увеличения скорости телеги

    bool first = true;                      // Флаг первого запуска
    bool llock = false;                     // Флаг закрытия левого крюка
    bool rlock = false;                     // Флаг закрытия правого крюка
};

#endif // DOCKER_H
