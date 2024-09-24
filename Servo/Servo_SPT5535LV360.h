#ifndef SERVO_SPT5535LV360_H
#define SERVO_SPT5535LV360_H

#include <cstdint>
#include <wiringPi.h>
#include <softPwm.h>

class Servo_SPT5535LV360
{
public:
    enum PWM {
        STOP    = 0,
        CV1     = 16,   // Минимальная скорость по часовой стрелке
        CV2     = 17,
        CV3     = 18,
        CV4     = 19,
        CV5     = 20,
        CV6     = 21,
        CV7     = 22,
        CV8     = 23,
        CV9     = 24,
        CV10    = 25,   // Максимальная скорость по часовой стрелке
        CCV1    = 14,   // Минимальная скорость против часовой стрелки
        CCV2    = 13,
        CCV3    = 12,
        CCV4    = 11,
        CCV5    = 10,
        CCV6    = 9,
        CCV7    = 8,
        CCV8    = 7,
        CCV9    = 6,
        CCV10   = 5    // Минимальная скорость против часовой стрелки
    };

public:
    Servo_SPT5535LV360() = delete;
    Servo_SPT5535LV360(uint8_t pin);

    void writePWM(PWM pwm);   // Установка ширины импульса для поворота сервопривода

private:
    int m_pin = 0;                     // Пин которому присоединена серва
};

#endif // SERVO_SPT5535LV360_H
