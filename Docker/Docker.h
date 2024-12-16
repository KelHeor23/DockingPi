/*!
    \file
    \brief Абстрактный класс описывающий поведение модулей стыковки
    \author Князев А.И
*/

#ifndef DOCKER_H
#define DOCKER_H

#include <chrono>
#include <iostream>
#include <string>

#include "../PayloadMechanisms/PCA9685/PCA9685.h"
#include "../PayloadMechanisms/Odometer/Odometer.h"
#include "DockerPinout.h"

using m_time = std::chrono::system_clock;

/*!
    \brief Абстрактный класс описывающий поведение модулей стыковки
*/
class Docker {
public:

    /*!
        \brief Конструктор создания модуля стыковки.
        Создает экземпляр модуля стыковки, забает базовое полежение сервов
    */
    Docker() {
        pca.set_pwm_freq(50.0);
        pca.set_pwm(PCA9685::PIN_LEFT_HOOK, 0, PCA9685::ms1500);
        pca.set_pwm(PCA9685::PIN_RIGHT_HOOK, 0, PCA9685::ms1500);

        /// Запускаю наблюдение за одометром
        odometerCargo.startObservePos();
    }

    virtual ~Docker(){}

    /*!
        \brief Функция работы модуля стыковки. Запускаемая в бесконечном цикле.
    */
    virtual void docking()      = 0;

    /*!
        \brief Функция расстыковки. Запускаемая в бесконечном цикле.
    */
    virtual void undocking()    = 0;

    /*!
        \brief Функция вызывающая connect в механизме обмена
    */
    virtual void connect()         = 0;

    /*!
        \brief Функция вращения сервы телеги по часовй стрелке
    */
    virtual void cargoCV(){
        cargoUnLock();
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 + PCA9685::step * 2);
    }

    /*!
        \brief Функция вращения сервы телеги против часовй стрелки
    */
    virtual void cargoCCV(){
        cargoUnLock();
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 - PCA9685::step * 2);
    }

    /*!
        \brief Функция вращения сервы телеги
    */
    void cargoMove(uint16_t speed = PCA9685::ms1500){
        cargoUnLock();
        pca.set_pwm(PCA9685::PIN_CARGO, 0, speed);
    }

    /*!
        \brief Функция остановки сервы телеги
    */
    virtual void cargoStop(){
        cargoLock();
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500);
    }

    /*!
        \brief Функция паузы стыковки. Запускаемая в бесконечном цикле.
    */
    virtual void stop(){
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500);
        cargoLock();
        odometerCargo.setCurState(0);
    }

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

public:
    /*!
    \brief Сообщение отправленное от мамы.
    Байты:
    0 - готовность
    1 - хуки закрылись
    2 - телега пришла к маме
    */
    std::string MSG_mama = "000";

    /*!
    \brief Сообщение отправленное от папы
    Байты:
    0 - готовность
    1 - стрела выдвинулась
    2 - дроны стянулись
    3 - телега покинула папу
    */
    std::string MSG_papa = "0000";

    /// Метка времени
    std::chrono::time_point<m_time> lastSwitchTime = m_time::now();

    /// Промежуток увеличения скорости телеги. мс.
    int cargoAcceleration = 300;

    /// Флаг первого запуска
    bool first = true;

    /// Флаг закрытия левого крюка
    bool llock = false;

    /// Флаг закрытия правого крюка
    bool rlock = false;

    /// Плата генерирующая ШИМ сигналы для серв
    PCA9685::PCA9685 pca{"/dev/i2c-2"};

    /// Скорость телеги в момент ее передачи
    std::uint16_t cargoTransferSpeed = PCA9685::ms1500;

    Odometer odometerCargo{PIN_ODOMETER_CARGO};

    int cntUndocking = 0;
};

#endif // DOCKER_H
