#include <ncurses.h>

#include "DockerPapa.h"

DockerPapa::DockerPapa() {
    //TODO: удалить как закончу с папой
    MSG_mama = "111";
}

void DockerPapa::docking()
{
    MSG_papa[0] = '1';
    if (MSG_mama[0] == '1'){
        if (MSG_papa[1] == '0')
            rodExtension();
        else if (MSG_mama[1] == '1' && MSG_papa[2] == '0'){
            pullingUp();
        } else if (MSG_papa[2] == '1' && MSG_papa[3] == '0') {

        }
    } else {
        undocking();
    }
}

void DockerPapa::undocking()
{
    MSG_papa[0] = '0';

    if (MSG_papa[1] == '0'){
        stop();
        return;
    }

    if (MSG_papa[2] == '1') {   // Сначала отпихиваем другой дрон
        pushAway();
    } else if (MSG_papa[1] == '1')  // А затем, убираем стрелу
        rodRetraction();
}

void DockerPapa::stop()
{
    servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
    servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
}

void DockerPapa::rodExtension()
{
    if (digitalRead(PIN_ROD_EXTENTION) == LOW){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CV10);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CCV2);
    } else {
        printw("done rodExtension\n");
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
        MSG_papa[1] = '1';
    }
}

void DockerPapa::rodRetraction()
{
    if (digitalRead(PIN_ROD_RETRACTED) == LOW){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CCV10);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CV2);
    } else {
        printw("done rodRetraction\n");
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
        MSG_papa[1] = '0';
    }
}

void DockerPapa::pullingUp()
{
    if (digitalRead(PIN_DOCKING_COMPL) == LOW){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CCV5);
    } else {
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        printw("done pullingUp\n");
        MSG_papa[2] = '1';
    }
}

void DockerPapa::pushAway()
{
    if (digitalRead(PIN_DOCKING_COMPL)){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CV5);
    } else {
        printw("done pushAway\n");
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        MSG_papa[2] = '0';
    }
}
