#include "DockerMama.h"

DockerMama::DockerMama() {
    MSG_papa = "1111";         // Сообщение отправленное от папы
    servoLeftHook.writePWM(Servo_DS3235_270::PWM::NEUTRAL);
    servoRightHook.writePWM(Servo_DS3235_270::PWM::NEUTRAL);
}

void DockerMama::docking()
{
    MSG_mama[0] = '1';
    if (MSG_papa[0] == '1'){
        if (MSG_mama[1] == '0'){    // Закрываем крюки
            lockingHooks();
        } else if (MSG_papa[2] == '1' && MSG_papa[3] == '0'){  // Стыковка закончилась, готовлю серво
            cargoTransferBegin();
        } else if (MSG_papa[3] == '1' && MSG_mama[2] == '0'){   // Папа передал телегу, останавливаю ее
            cargoTransferEnding();
        } else if (MSG_mama[2] == '1'){                         // Телега пришла, заканчиваем
            stop();
        }
    } else {
        undocking();
    }
}

void DockerMama::undocking()
{
    MSG_mama[0] = '0';
    if (MSG_mama[1] == '1'){
        servoLeftHook.writePWM(Servo_DS3235_270::PWM::NEUTRAL);
        servoRightHook.writePWM(Servo_DS3235_270::PWM::NEUTRAL);
    }

    if (digitalRead(PIN_CARGO_ON_BORDER) == HIGH && digitalRead(PIN_CARGO_AT_HOME) == LOW)
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::CCV10);
    else
        servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
}

void DockerMama::stop()
{
    servoRod.writePWM(Servo_SPT5535LV360::PWM::STOP);
    servoCargo.writePWM(Servo_SPT5535LV360::PWM::STOP);
}

void DockerMama::lockingHooks()
{
    if (digitalRead(PIN_LEFT_HOOK_ACTIVE) == HIGH) {
        servoLeftHook.writePWM(Servo_DS3235_270::PWM::CCV2);
    }

    if (digitalRead(PIN_RIGHT_HOOK_ACTIVE) == HIGH) {
        servoRightHook.writePWM(Servo_DS3235_270::PWM::CV2);
    }
    if (digitalRead(PIN_LEFT_HOOK_ACTIVE) == HIGH && digitalRead(PIN_RIGHT_HOOK_ACTIVE) == HIGH){
        MSG_mama[1] = '1';
    }
}

void DockerMama::cargoTransferBegin()
{
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        servoCargo.increaseSpeedCargoCV();
        lastSwitchTime = m_time::now();
    }
}

void DockerMama::cargoTransferEnding()
{
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_time::now() - lastSwitchTime).count();
    if (elapsedTime >= cargoAcceleration){
        servoCargo.decreaseSpeedCargoCV();
        lastSwitchTime = m_time::now();
    }

    if (digitalRead(PIN_CARGO_AT_HOME) == HIGH)
        MSG_mama[2] = '1';
}
