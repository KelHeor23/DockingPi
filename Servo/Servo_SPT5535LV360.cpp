#include "Servo_SPT5535LV360.h"

Servo_SPT5535LV360::Servo_SPT5535LV360(int pin) : m_pin(pin) {
    softPwmCreate(m_pin, PWM::SPT5535LV360::STOP, PWM::SPT5535LV360::CV10); // Создание PWM на пине для управления сервоприводом
}

void Servo_SPT5535LV360::writePWM(PWM::SPT5535LV360 pwm){
    softPwmWrite(m_pin, pwm);
}
