#include <ncurses.h>
#include <iostream>
#include <wiringPi.h>

#include "DockerPapa.h"

DockerPapa::DockerPapa() {}

void DockerPapa::docking()
{
    MSG_mama = "111";
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

    if (digitalRead(PIN_CARGO_ON_BORDER) == HIGH && digitalRead(PIN_CARGO_AT_HOME) == LOW){
        cargoUnLock();
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms2500);
    }
    else {
        cargoTransferSpeed = PCA9685::ms1500;
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500);
    }
}

void DockerPapa::stop()
{
    pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
    pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500);
    cargoLock();
}

void DockerPapa::connect()
{
    client.connect(address_g, port_g);

    std::cout << "Connection complite!" << std::endl;
}

void DockerPapa::rodExtension()
{
    if (digitalRead(PIN_ROD_EXTENTION) == LOW){
        cargoUnLock();
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms2000);
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 + PCA9685::step * 2);
    } else {
        printw("done rodExtension\n");
        stop();
        MSG_papa[1] = '1';
    }
}

void DockerPapa::rodRetraction()
{
    if (digitalRead(PIN_ROD_RETRACTED) == LOW){
        cargoUnLock();
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1000);
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 - PCA9685::step * 1);
    } else {
        printw("done rodRetraction\n");
        stop();
        MSG_papa[1] = '0';
    }
}

void DockerPapa::pullingUp()
{
    if (analogRead(PIN_DOCKING_COMPL) == HIGH){
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
        printw("done pullingUp\n");
        MSG_papa[2] = '1';
    } else if (analogRead(PIN_ROD_RETRACTED) == HIGH){
        undocking();
    } else {
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1000);
    }
}

void DockerPapa::pushAway()
{
    if (analogRead(PIN_DOCKING_COMPL) == HIGH){
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms2000);
    } else {
        printw("done pushAway\n");
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
        MSG_papa[2] = '0';
    }
}

void DockerPapa::cargoTransfer()
{
    if (first){
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500);
        first = false;
    }

    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        if (cargoTransferSpeed + PCA9685::step < PCA9685::ms2500)
            cargoTransferSpeed += PCA9685::step;
        pca.set_pwm(PCA9685::PIN_CARGO, 0,  cargoTransferSpeed);
        lastSwitchTime = m_time::now();
    }
    if (analogRead(PIN_CARGO_ON_BORDER) == LOW && analogRead(PIN_CARGO_AT_HOME) == LOW){
        MSG_papa[3] = '1';
        printw("done cargoTransfer\n");
    }
}

void DockerPapa::cargoTransferEnding()
{
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        if (cargoTransferSpeed - PCA9685::step > PCA9685::ms1500)
            cargoTransferSpeed -= PCA9685::step;
        pca.set_pwm(PCA9685::PIN_CARGO, 0,  cargoTransferSpeed);
        std::cout << "cargoTransferEnding" << std::endl;        
        lastSwitchTime = m_time::now();
    }
}
