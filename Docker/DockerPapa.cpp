#include "DockerPapa.h"

DockerPapa::DockerPapa() {}

void DockerPapa::docking()
{
    rodExtension();
}

void DockerPapa::undocking()
{

}

void DockerPapa::rodExtension()
{
    servoRod.writePWM(Servo_SPT5535LV360::PWM::CV10);
    servoCargo.writePWM(Servo_SPT5535LV360::PWM::CCV2);
}
