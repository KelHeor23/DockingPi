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
        } else if (MSG_mama[2] == '0'){   // Папа передал телегу, останавливаю ее
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
    startCargo = false;
    // В этом месте порадок сообщений важен
    papaExchange();
    MSG_mama[0] = '0';

    if (MSG_papa[2] == '0'){
        if (rlock || llock){
            RHunlock();
            LHunlock();
            MSG_mama[1] = '0';
            std::cout << "all hooks unlocked" << std::endl;
        }
    }

    stop();
}

void DockerMama::connect()
{
    std::cout << "Connection complite!" << std::endl;
}

void DockerMama::lockingHooks()
{
    if (digitalRead(PIN_LEFT_HOOK_ACTIVE) == HIGH){
        std::cout << "l+" << std::endl;
        countLH++;
    } else {
        countLH = 0;
        std::cout << "l-" << std::endl;
    }

    if (digitalRead(PIN_RIGHT_HOOK_ACTIVE) == HIGH){
        countRH++;
        std::cout << "r+" << std::endl;
    } else {
        countRH = 0;
        std::cout << "r-" << std::endl;
    }

    if (countLH == 2) {
        pca.set_pwm(PCA9685::PIN_LEFT_HOOK, 0, PCA9685::ms1000 - 0x25);
        llock = true;
        std::cout << "LHlocked" << std::endl;
    } else {
        //LHunlock();
        //std::cout << "LHunlocked" << std::endl;
    }

    if (countRH == 2) {
        pca.set_pwm(PCA9685::PIN_RIGHT_HOOK, 0, PCA9685::ms2000 + 0x27);
        rlock = true;
        std::cout << "RHlocked" << std::endl;
    } else {
        //RHunlock();
        //std::cout << "RHunlocked" << std::endl;
    }

    if (llock && rlock){
        std::cout << "all hooks locked" << std::endl;
        MSG_mama[1] = '1';
    }
}

void DockerMama::cargoTransferBegin()
{
    odometerCargo.setCurState(1);

    if (odometerCargo.getCurPos() > 0){
        startCargo = true;
    }

    cargoMove(PCA9685::ms2000 + 0x20);
    odometerCargo.setCurState(1);
}

void DockerMama::cargoTransferEnding()
{
    if (digitalRead(PIN_CARGO_AT_HOME) == HIGH)
        countCH++;
    else
        countCH = 0;

    if (countCH == 10) {
        cargoStop();
        MSG_mama[2] = '1';
    }
}

void DockerMama::papaExchange()
{
    serverMama.exchange();
    serverMama.writeMsgMama(MSG_mama);
    MSG_papa = serverMama.readMsgPapa();
}
