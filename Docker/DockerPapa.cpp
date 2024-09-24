#include "DockerPapa.h"

DockerPapa::DockerPapa() {}

void DockerPapa::docking()
{
    rodExtension();
}

void DockerPapa::undocking()
{
    rodRetraction();
}

void DockerPapa::rodRetraction()
{
    if (!digitalRead(PIN_ROD_RETRACTED)){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CCV10);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CV1);
    } else {
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
    }
}

void DockerPapa::rodExtension()
{
    if (!digitalRead(PIN_ROD_EXTENTION)){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CV10);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CCV1);
    } else {
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
    }
}
