#include "Servo_SPT5535LV360.h"

Servo_SPT5535LV360::Servo_SPT5535LV360(uint8_t pin) : m_pin(pin) {
    softPwmCreate(m_pin, 0, 100); // Создание PWM на пине для управления сервоприводом
}

void Servo_SPT5535LV360::writePWM(PWM pwm){
    currSpeed = pwm;
    softPwmWrite(m_pin, currSpeed);
}

void Servo_SPT5535LV360::increaseSpeedCargoCV(){
    if (currSpeed < CV10)
        currSpeed = static_cast<PWM>(static_cast<int>(currSpeed) + 1); // Да простят меня духи машины за такую хрень
    softPwmWrite(m_pin, currSpeed);
}

void Servo_SPT5535LV360::decreaseSpeedCargoCV(){
    if (currSpeed > STOP)
        currSpeed = static_cast<PWM>(static_cast<int>(currSpeed) - 1); // Да простят меня духи машины за такую хрень
    softPwmWrite(m_pin, currSpeed);
}
