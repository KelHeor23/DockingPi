#include <iostream>
#include <wiringPi.h>

#include "DockerPapa.h"

#include "../config.h"

DockerPapa::DockerPapa() {}

void DockerPapa::docking()
{
    MSG_papa[0] = '1';

    mamaExchange();

    if (MSG_mama[0] == '1'){
        cntUndocking = 0;
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
        cntUndocking++;
        if (cntUndocking > 3){
            undocking();
            cntUndocking = 0;
        }
    }
}

void DockerPapa::undocking()
{
    // В этом месте порадок сообщений важен
    mamaExchange();
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

    /*if (digitalRead(PIN_CARGO_ON_BORDER) == HIGH && digitalRead(PIN_CARGO_AT_HOME) == LOW){
        cargoUnLock();
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms2500);
    }
    else {
        cargoTransferSpeed = PCA9685::ms1500;
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500);
    }*/
    if (MSG_papa[1] == '0')
        firstFlag = true;
}

void DockerPapa::connect()
{
    std::cout << "Connection complite!" << std::endl;
}

void DockerPapa::rodExtension()
{
    if (firstFlag){
        cargoPosStart = odometerCargo.getCurPos();
        firstFlag = false;
    }

    if (digitalRead(PIN_ROD_EXTENTION) == HIGH && odometerCargo.getCurPos() <= cargoPosStart - balance_cargo_g){
        stop();
        std::cout << "done rodExtension\n" << std::endl;
        MSG_papa[1] = '1';
        return;
    }

    if (digitalRead(PIN_ROD_EXTENTION) == LOW){
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms2000 - 0x5);
    } else {
        usleep(1000);
        if (digitalRead(PIN_ROD_EXTENTION) == HIGH)
            pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
    }

    if (odometerCargo.getCurPos() > cargoPosStart - balance_cargo_g){
        odometerCargo.setCurState(-1);
        cargoMove(PCA9685::ms1500 - PCA9685::step * 2 + 0x15);
    } else
        cargoStop();
}

void DockerPapa::rodRetraction()
{
    if (digitalRead(PIN_ROD_RETRACTED) == HIGH && odometerCargo.getCurPos() >= cargoPosStart){
        stop();
        std::cout << "done rodRetraction\n" << std::endl;
        MSG_papa[1] = '0';
        return;
    }

    if (digitalRead(PIN_ROD_RETRACTED) == LOW){        
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1000 - 0x10);
    } else {
        usleep(1000);
        if (digitalRead(PIN_ROD_RETRACTED) == HIGH)
            pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
    }

    if (odometerCargo.getCurPos() < cargoPosStart){
        odometerCargo.setCurState(1);
        cargoMove(PCA9685::ms1500 + PCA9685::step * 2 - 0xF);
    } else
        cargoStop();
}

void DockerPapa::pullingUp()
{
    if (digitalRead(PIN_DOCKING_COMPL) == HIGH){
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
        std::cout << "done pullingUp\n" << std::endl;
        MSG_papa[2] = '1';
    } else if (digitalRead(PIN_ROD_RETRACTED) == HIGH){
        undocking();
    } else {
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1000);
    }
}

void DockerPapa::pushAway()
{
    if (digitalRead(PIN_DOCKING_COMPL) == HIGH){
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms2000);
    } else {
        std::cout <<  "done pushAway\n" << std::endl;
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
        MSG_papa[2] = '0';
    }
}

void DockerPapa::cargoTransfer()
{
    if (first){
        cargoStop();
        first = false;
    }

    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        if (cargoTransferSpeed + PCA9685::step < PCA9685::ms2500)
            cargoTransferSpeed += PCA9685::step;
        cargoMove(cargoTransferSpeed);
        lastSwitchTime = m_time::now();
    }
    /*if (digitalRead(PIN_CARGO_ON_BORDER) == LOW && digitalRead(PIN_CARGO_AT_HOME) == LOW){
        MSG_papa[3] = '1';
        std::cout <<"done cargoTransfer\n" << std::endl;
    }*/
}

void DockerPapa::cargoTransferEnding()
{
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        if (cargoTransferSpeed - PCA9685::step > PCA9685::ms1500)
            cargoTransferSpeed -= PCA9685::step;
        cargoMove(cargoTransferSpeed);
        std::cout << "cargoTransferEnding" << std::endl;        
        lastSwitchTime = m_time::now();
    }
}

void DockerPapa::mamaExchange()
{
    clientPapa.exchange();
    clientPapa.writeMsgPapa(MSG_papa);
    MSG_mama = clientPapa.readMsgMama();
}
