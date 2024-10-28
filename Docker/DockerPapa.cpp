#include <ncurses.h>
#include <iostream>

#include "DockerPapa.h"

DockerPapa::DockerPapa() {}

void DockerPapa::docking()
{
    MSG_papa[0] = '1';
    if (MSG_mama[0] == '1'){
        if (MSG_papa[1] == '0')
            rodExtension();
        else if (MSG_mama[1] == '1' && MSG_papa[2] == '0'){
            pullingUp();
        } else if (MSG_papa[2] == '1' && MSG_papa[3] == '0') {
            cargoTransfer();
        } else if (MSG_papa[3] == '1' && MSG_mama[1] == '0') {
            cargoTransferEnding();
        } else if (MSG_mama[2] == '1') {
            stop();
        }
    } else {
        undocking();
    }
}

void DockerPapa::undocking()
{
    MSG_papa[0] = '0';
    first = true;

    if (MSG_papa[1] == '0'){
        stop();
        return;
    }

    if (MSG_papa[2] == '1') {   // Сначала отпихиваем другой дрон
        pushAway();
    } else if (MSG_papa[1] == '1')  // А затем, убираем стрелу
        rodRetraction();

    if (digitalRead(PIN_CARGO_ON_BORDER) == HIGH && digitalRead(PIN_CARGO_AT_HOME) == LOW)
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CV10);
    else
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
}

void DockerPapa::stop()
{
    servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
    servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
}

void DockerPapa::connect()
{
    std::string address = "10.42.0.1";
    std::size_t port    = 8000;
    client.connect(address, port);
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
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CV1);
    } else {
        printw("done rodRetraction\n");
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
        MSG_papa[1] = '0';
    }
}

void DockerPapa::pullingUp()
{
    if (digitalRead(PIN_DOCKING_COMPL) == HIGH){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        printw("done pullingUp\n");
        MSG_papa[2] = '1';
    } else if (digitalRead(PIN_ROD_RETRACTED) == HIGH){
        undocking();
    } else {
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CCV5);
    }
}

void DockerPapa::pushAway()
{
    if (digitalRead(PIN_DOCKING_COMPL) == HIGH){
        servoRod.writePWM(Servo_SPT5535LV360::PWM::CV5);
    } else {
        printw("done pushAway\n");
        servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
        MSG_papa[2] = '0';
    }
}

void DockerPapa::cargoTransfer()
{
    if (first){
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::NEUTRAL); // Колхоз, нужен для перебора enum
        first = false;
    }

    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        servoCargo.increaseSpeedCargoCV();
        lastSwitchTime = m_time::now();
    }
    if (digitalRead(PIN_CARGO_ON_BORDER) == LOW && digitalRead(PIN_CARGO_AT_HOME) == LOW){
        MSG_papa[3] = '1';
        printw("done cargoTransfer\n");
    }
}

void DockerPapa::cargoTransferEnding()
{
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        std::cout << "cargoTransferEnding" << std::endl;
        servoCargo.decreaseSpeedCargoCV();
        lastSwitchTime = m_time::now();
    }
}
