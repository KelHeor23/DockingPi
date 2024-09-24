#ifndef SERVO_DS3235_270_H
#define SERVO_DS3235_270_H

#include <cstdint>
#include <wiringPi.h>
#include <softPwm.h>

class Servo_DS3235_270
{
public:
    enum PWM {
        CCV10 = 5,
        CCV9 = 6,
        CCV8 = 7,
        CCV7 = 8,
        CCV6 = 9,
        CCV5 = 10,
        CCV4 = 11,
        CCV3 = 12,
        CCV2 = 13,
        CCV1 = 14,
        NEUTRAL = 15, // нейтральное положение
        CV1 = 16,
        CV2 = 17,
        CV3 = 18,
        CV4 = 19,
        CV5 = 20,
        CV6 = 21,
        CV7 = 22,
        CV8 = 23,
        CV9 = 24,
        CV10 = 25
    };

public:
    Servo_DS3235_270() = delete;
    Servo_DS3235_270(uint8_t pin);

    void writePWM(PWM pwm);   // Установка ширины импульса для поворота сервопривода

private:
    int m_pin = 0;                     // Пин которому присоединена серва
};

#endif // SERVO_DS3235_270_H
