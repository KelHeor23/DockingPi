#include "Servo_DS3235_270.h"

Servo_DS3235_270::Servo_DS3235_270(int pin) : m_pin(pin) {
}

void Servo_DS3235_270::writePWM(PWM pwm){
    softPwmCreate(m_pin, 0, 100); // Создание PWM на пине для управления сервоприводом
    softPwmWrite(m_pin, pwm);
    delay(100);
    softPwmStop(m_pin); // Отключаю аналоговый сигнал, иначе дергается
}

