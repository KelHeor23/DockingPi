/*!
    \file
    \brief Абстрактный класс описывающий поведение модулей стыковки
    \author Князев А.И
*/

#ifndef DOCKER_H
#define DOCKER_H

#include <chrono>
#include <string>

#include "../Servo/Servo.h"
#include "DockerPinout.h"

using m_time = std::chrono::system_clock;

/*!
    \brief Абстрактный класс описывающий поведение модулей стыковки
*/
class Docker {
public:

    /*!
        \brief Конструктор создания модуля стыковки.
        Создает экземпляр модуля стыковки, инициализирует пины и сервы
    */
    Docker() : servoRod(PIN_ROD), servoCargo(PIN_CARGO),
        servoRightHook(PIN_RIGHT_HOOK), servoLeftHook(PIN_LEFT_HOOK) {
        pinMode(PIN_ROD_EXTENTION, INPUT);
        pinMode(PIN_ROD_RETRACTED, INPUT);
        pinMode(PIN_DOCKING_COMPL, INPUT);
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
        \brief Функция паузы стыковки. Запускаемая в бесконечном цикле.
    */
    virtual void stop()         = 0;

    /*!
        \brief Функция вращения сервы для движения телеги по часовой стрелке
    */
    void cargoCV(){
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CV2);
    }
    
    /*!
        \brief Функция вращения сервы для движения телеги против часовой стрелки
    */
    void cargoCCV(){
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CCV3);
    }

public:
    /// Серва штанги
    Servo_SPT5535LV360  servoRod;
    /// Серва телеги
    Servo_SPT5535LV360  servoCargo;
    /// Серва правого крюка
    Servo_DS3235_270    servoRightHook;
    /// Серва левого крюка
    Servo_DS3235_270    servoLeftHook;

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
};

#endif // DOCKER_H
