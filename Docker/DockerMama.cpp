#include <iostream>
#include <wiringPi.h>

#include "DockerMama.h"

#include "../config.h"

DockerMama::DockerMama() {
}

void DockerMama::docking()
{
    MSG_mama[0] = '1';
    papaExchange();

    if (MSG_papa[0] == '1'){
        cntUndocking = 0;
        if (MSG_mama[1] == '0'){    // Закрываем крюки
            lockingHooks();
            cargoUnLock();          // Готовимся принимать телегу
        } else if (MSG_papa[2] == '1' && MSG_papa[3] == '0'){  // Стыковка закончилась, готовлю серво
            cargoTransferBegin();
        } else if (MSG_papa[3] == '1' && MSG_mama[2] == '0'){   // Папа передал телегу, останавливаю ее
            cargoTransferEnding();
        } else if (MSG_mama[2] == '1'){                         // Телега пришла, заканчиваем
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

void DockerMama::undocking()
{
    // В этом месте порадок сообщений важен
    papaExchange();
    MSG_mama[0] = '0';

    if (rlock || llock){
        pca.set_pwm(PCA9685::PIN_LEFT_HOOK, 0, PCA9685::ms1500);
        pca.set_pwm(PCA9685::PIN_RIGHT_HOOK, 0, PCA9685::ms1500);
        MSG_mama[1] = '0';
        rlock = false;
        llock = false;
    }

    /*if (digitalRead(PIN_CARGO_ON_BORDER) == HIGH && digitalRead(PIN_CARGO_AT_HOME) == LOW)
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms500);
    else {
        cargoTransferSpeed = PCA9685::ms1500;
        stop();
    }*/
}

void DockerMama::connect()
{
    std::cout << "Connection complite!" << std::endl;
}

void DockerMama::lockingHooks()
{ 
    if (digitalRead(PIN_LEFT_HOOK_ACTIVE) == HIGH) {
        pca.set_pwm(PCA9685::PIN_LEFT_HOOK, 0, PCA9685::ms1000 + 0xA);
        llock = true;
    }

    if (digitalRead(PIN_RIGHT_HOOK_ACTIVE) == HIGH) {
        pca.set_pwm(PCA9685::PIN_RIGHT_HOOK, 0, PCA9685::ms2000);
        rlock = true;
    }

    if (llock && rlock){
        MSG_mama[1] = '1';
    }
}

void DockerMama::cargoTransferBegin()
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
}

void DockerMama::cargoTransferEnding()
{
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        if (cargoTransferSpeed - PCA9685::step > PCA9685::ms1500)
            cargoTransferSpeed -= PCA9685::step;
        cargoMove(cargoTransferSpeed);
        lastSwitchTime = m_time::now();
    }
    odometerCargo.setCurState(1);

    if (odometerCargo.getCurPos() >= cargoAtHome){
        cargoStop();
        MSG_mama[2] = '1';
    }

    /*if (digitalRead(PIN_CARGO_AT_HOME) == HIGH)
        MSG_mama[2] = '1';*/
}

void DockerMama::papaExchange()
{
    serverMama.exchange();
    serverMama.writeMsgMama(MSG_mama);
    MSG_papa = serverMama.readMsgPapa();
}
