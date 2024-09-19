#include "Servo_SPT5535LV360.h"

Servo_SPT5535LV360::Servo_SPT5535LV360(int pin) : m_pin(pin) {
    softPwmCreate(m_pin, 0, 100); // Создание PWM на пине для управления сервоприводом
}

void Servo_SPT5535LV360::writePWM(PWM pwm){
    softPwmWrite(m_pin, pwm) ;
}
