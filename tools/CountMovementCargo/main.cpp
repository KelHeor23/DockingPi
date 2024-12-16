#include <iostream>
#include <thread>
#include <termios.h>
#include <wiringPi.h>

#include "../../PayloadMechanisms/Odometer/Odometer.h"
#include "../../Docker/DockerPinout.h"
#include "../../Common/ButtonHandler.h"
#include "../../PayloadMechanisms/PCA9685/PCA9685.h"

using namespace std;

std::atomic_char button;
PCA9685::PCA9685 pca{"/dev/i2c-2"};
Odometer odometr{PIN_ODOMETER_CARGO};

/*!
        \brief Функция закрытия замка движения телеги
    */
void cargoLock(){
    /// У сервы закрытия замка телеги более узкий диапазон вращения
    pca.set_pwm(PCA9685::PIN_CARGO_LOCK, 0, PCA9685::ms2000 + PCA9685::step * 2);
}

/*!
        \brief Функция открытия замка движения телеги
    */
void cargoUnLock(){
    /// У сервы закрытия замка телеги более узкий диапазон вращения
    pca.set_pwm(PCA9685::PIN_CARGO_LOCK, 0, PCA9685::ms1000 - PCA9685::step * 2);
}

/*!
        \brief Функция вращения сервы телеги по часовй стрелке
    */
void cargoCV(){
    cargoUnLock();
    pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 + PCA9685::step * 2);
}

/*!
        \brief Функция вращения сервы телеги против часовй стрелки
    */
void cargoCCV(){
    cargoUnLock();
    pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 - PCA9685::step * 2);
}

/*!
        \brief Функция паузы стыковки. Запускаемая в бесконечном цикле.
    */
void stop(){
    pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
    pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500);
    cargoLock();
}

int main()
{
    if (wiringPiSetup() == -1) {
        std::cerr << "Ошибка инициализации WiringPi." << std::endl;
        return 0;
    }

    ButtonHandler::Button btn;
    btn.setAllowedRegex(std::regex("[1-5]"));
    btn.run();

    bool first = true;
    while (true) {
        switch (btn.getButton()) {
        case '1':
            cargoCV();
            first = true;
            break;
        case '2':
            cargoCCV();
            first = true;
            break;
        case '3':
            cargoLock();
            stop();
            if (first){
                std::cout << "Current pos: " << odometr.getCurPos() << std::endl;
                first = false;
            }
            break;
        }
    }

    return 0;
}
