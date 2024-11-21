#include "Odometer.h"

#include <wiringPi.h>
#include <thread>
#include <chrono>

Odometer::Odometer(uint8_t m_pin, int m_hz, int m_curPos):
    pin(m_pin), hz(1000 / m_hz), curPos(m_curPos)
{
}

void Odometer::startObservePos()
{
    std::thread t([this]() {
        while (true) {
            if (flag == false && digitalRead(pin) == HIGH){
                flag = true;
                changePos();
            } else if (flag == true && digitalRead(pin) == LOW){
                flag = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    });
    t.detach();
}

void Odometer::changePos()
{
    switch (curState) {
    case -1:
        curPos--;
        break;
    case 1:
        curPos++;
        break;
    default:
        break;
    }
}

void Odometer::setHz(int newHz)
{
    hz = newHz;
}

std::atomic<int> Odometer::getCurPos() const
{
    return curPos.load(std::memory_order_relaxed);;
}

void Odometer::setCurState(const int &newCurState)
{
    curState = newCurState;
}
