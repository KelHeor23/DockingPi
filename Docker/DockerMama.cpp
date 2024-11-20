#include "DockerMama.h"
#include <iostream>
#include <wiringPi.h>

DockerMama::DockerMama() {
}

void DockerMama::docking()
{    
    MSG_mama[0] = '1';
    if (MSG_papa[0] == '1'){
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
        undocking();
    }
}

void DockerMama::undocking()
{
    MSG_mama[0] = '0';
    if (rlock || llock){
        pca.set_pwm(PCA9685::PIN_LEFT_HOOK, 0, PCA9685::ms1500);
        pca.set_pwm(PCA9685::PIN_RIGHT_HOOK, 0, PCA9685::ms1500);
        MSG_mama[1] = '0';
        rlock = false;
        llock = false;
    }

    if (digitalRead(PIN_CARGO_ON_BORDER) == HIGH && digitalRead(PIN_CARGO_AT_HOME) == LOW)
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms500);
    else {
        cargoTransferSpeed = PCA9685::ms1500;
        stop();
    }
}

void DockerMama::connect()
{
    server.connect(address_g, port_g);

    std::cout << "Connection complite!" << std::endl;
}

void DockerMama::lockingHooks()
{ 
    if (digitalRead(PIN_LEFT_HOOK_ACTIVE) == HIGH) {
        pca.set_pwm(PCA9685::PIN_LEFT_HOOK, 0, PCA9685::ms1000);
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
}

void DockerMama::cargoTransferEnding()
{
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        if (cargoTransferSpeed - PCA9685::step > PCA9685::ms1500)
            cargoTransferSpeed -= PCA9685::step;
        pca.set_pwm(PCA9685::PIN_CARGO, 0,  cargoTransferSpeed);
        lastSwitchTime = m_time::now();
    }

    if (digitalRead(PIN_CARGO_AT_HOME) == HIGH)
        MSG_mama[2] = '1';
}
