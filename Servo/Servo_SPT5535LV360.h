/*!
    \file
    \brief Класс работы с сервой SPT5535LV360
    \author Князев А.И

    Класс для работы с сервой. Область поворота сервы- 360 градусов
*/
#ifndef SERVO_SPT5535LV360_H
#define SERVO_SPT5535LV360_H

#include <cstdint>
#include <wiringPi.h>
#include <softPwm.h>

class Servo_SPT5535LV360
{
public:
    /// \brief enum, хранящий скорости. CV - по часовой, CCV - против часовой
    enum PWM {
        /// Полная остановка сервы
        STOP    = 0,
        /// Минимальная скорость по часовой стрелке
        CV1     = 16,
        CV2     = 17,
        CV3     = 18,
        CV4     = 19,
        CV5     = 20,
        CV6     = 21,
        CV7     = 22,
        CV8     = 23,
        CV9     = 24,
        /// Максимальная скорость по часовой стрелке
        CV10    = 25,
        /// Нетральная позиция
        NEUTRAL = 15,
        /// Минимальная скорость против часовой стрелки
        CCV1    = 14,
        CCV2    = 13,
        CCV3    = 12,
        CCV4    = 11,
        CCV5    = 10,
        CCV6    = 9,
        CCV7    = 8,
        CCV8    = 7,
        CCV9    = 6,
        /// Максимальная скорость против часовой стрелки
        CCV10   = 5
    };

public:
    Servo_SPT5535LV360() = delete;

    /*!
        \brief Конструктор запоминающий пин, к которому подключена серва
        \param[in] pin Номер пина
    */
    Servo_SPT5535LV360(uint8_t pin);

    /*!
        \brief Передача в серву импульса определенной ширины, для установки скорости вращения
        \param[in] pwm Ширина импульса. Значения из enum PWM
    */
    void writePWM(PWM pwm);

    /*!
        Инкрементирование скорости вращения телеги по часовой стрелке
    */
    void increaseSpeedCargoCV();

    /*!
        Декрементирование скорости вращения телеги по часовой стрелке
    */
    void decreaseSpeedCargoCV();

private:    
    int m_pin = 0; ///< Пин которому присоединена серва

    PWM currSpeed = STOP; ///< Текущая скорость вращения сервы
};

#endif // SERVO_SPT5535LV360_H
