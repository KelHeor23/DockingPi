#include "DockerPapa.h"

DockerPapa::DockerPapa() {
    //TODO:
    MSG_mama = "111";
}

void DockerPapa::docking()
{
    MSG_papa[0] = '1';
    if (MSG_mama[0] == '1'){
        if (MSG_papa[1] == '1')
            rodExtension();
        else if (MSG_mama[1] == '1' && MSG_papa[2] == '0')
            pullingUp();
    } else {
        undocking();
    }
}

void DockerPapa::undocking()
{
    MSG_papa[0] = '0';

    if (MSG_papa[2] == '1') {   // Сначала отпихиваем другой дрон
        pushAway();
    } else if (MSG_papa[1] == '1')  // А затем, убираем стрелу
        rodRetraction();    

}

void DockerPapa::rodExtension()
{
    if (!digitalRead(PIN_ROD_EXTENTION)){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CV10);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CCV1);
    } else {
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
        MSG_papa[1] = '1';
    }
}

void DockerPapa::rodRetraction()
{
    if (!digitalRead(PIN_ROD_RETRACTED)){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CCV10);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CV1);
    } else {
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
        MSG_papa[1] = '0';
    }
}

void DockerPapa::pullingUp()
{
    if (!digitalRead(PIN_DOCKING_COMPL)){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CCV5);
    } else {
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        MSG_papa[2] = '1';
    }
}

void DockerPapa::pushAway()
{
    if (digitalRead(PIN_DOCKING_COMPL)){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CV5);
    } else {
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        MSG_papa[2] = '0';
    }
}
