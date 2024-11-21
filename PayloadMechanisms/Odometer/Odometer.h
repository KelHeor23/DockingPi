#ifndef ODOMETER_H
#define ODOMETER_H

#include <cstdint>
#include <atomic>

class Odometer
{
public:
    Odometer() = delete;

    /*!
        \brief Конструктор одометра.
        \param[in] pin Пин куда подключено устройство
        \param[in] m_hz Частота проверки текущего положения одометра
        \param[in] m_curPos Текущее значение счетчика позиции
    */
    Odometer(uint8_t m_pin, int m_hz = 1000, int m_curPos = 0);

    /// Функция запускающая наблюдение за одометром позиции
    void startObservePos();

    /// Классический сеттер частоты проверки счетчика
    void setHz(int newHz);

    /// Геттер возвращающий текущее положение телеги
    std::atomic<int> getCurPos() const;

    /// Функция устанавливающая направление текущего вращения
    void setCurState(const int &newCurState);

private:
    /// Функция меняющая текузее значени положения, в зависимости от curState
    void changePos();

private:
    /// Счетчик, определяющий текущую позицию
    std::atomic<int> curPos{0};

    /// Значение условно задающее куда движется телега
    std::atomic<int> curState{0};

    /// Частота проверки счетчика
    int hz = 0;

    /// Пин куда подключено устройство
    uint8_t pin = 0;

    /// Флаг активации
    bool flag = false;
};

#endif // ODOMETER_H
