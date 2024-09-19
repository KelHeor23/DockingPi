#include "Servo_SPT5535LV360.h"

Servo_SPT5535LV360::Servo_SPT5535LV360(int pin) : m_pin(pin) {
}

void Servo_SPT5535LV360::writePWM(PWM::SPT5535LV360 pwm){
    softPwmCreate(m_pin, pwm, 100); // Создание PWM на пине для управления сервоприводом
}

void Servo_SPT5535LV360::stop()
{
    softPwmStop(m_pin);
}
