#ifndef DOCKER_H
#define DOCKER_H

#include "../Servo/Servo.h"

#include "DockerPinout.h"



class Docker {
public:
    Docker() : servoRod(PIN_ROD), servoCargo(PIN_CARGO),
        servoRightHook(PIN_RIGHT_HOOK), servoLeftHook(PIN_LEFT_HOOK) {}

    virtual ~Docker(){}

    virtual void docking()      = 0;
    virtual void undocking()    = 0;

public:
    Servo_SPT5535LV360  servoRod;       // Серва штанги
    Servo_SPT5535LV360  servoCargo;     // Серва телеги
    Servo_DS3235_270    servoRightHook; // Серва правого крюка
    Servo_DS3235_270    servoLeftHook;  // Серва левого крюка
};

#endif // DOCKER_H
