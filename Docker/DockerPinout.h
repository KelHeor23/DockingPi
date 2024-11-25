/*!
    \file
    \brief Файл, хранящий распиновку
    \author Князев А.И

    Файл, хранящий распиновку устрйоства. Таблицу можно посмотреть непосредсвтенно на устрйостве, введя в терминале команду "gpio readall"
*/
#ifndef DOCKERPINOUT_H
#define DOCKERPINOUT_H

#include <inttypes.h>

///Список пинов находящийхся на плте PCA9685
namespace PCA9685 {
    /// Пин сервы левого крюка
    constexpr uint8_t PIN_LEFT_HOOK         = 0;
    /// Пин сервы правого крюка
    constexpr uint8_t PIN_RIGHT_HOOK        = 1;
    /// Пин стрелы
    constexpr uint8_t PIN_ROD               = 2;
    /// Пин сервы замока тележки
    constexpr uint8_t PIN_CARGO_LOCK        = 3;
    /// Пин телеги
    constexpr uint8_t PIN_CARGO             = 4;
}

/// Пин одометра телеги
constexpr uint8_t PIN_ODOMETER_CARGO     = 2;
/// Пин стрела выдвинута
constexpr uint8_t PIN_ROD_EXTENTION     = 14;
/// Пин левый крюк активирован
constexpr uint8_t PIN_LEFT_HOOK_ACTIVE  = 13;
/// Пин правый крюк активирован
constexpr uint8_t PIN_RIGHT_HOOK_ACTIVE = 15;
/// Пин телега на границе
constexpr uint8_t PIN_CARGO_ON_BORDER   = 16;
/// Пин телега на домашней/стартовой позиции
constexpr uint8_t PIN_CARGO_AT_HOME     = 21;
/// Пин стыковка завершена
constexpr uint8_t PIN_DOCKING_COMPL     = 24;
/// Пин стрела задвинута
constexpr uint8_t PIN_ROD_RETRACTED     = 25;

#endif // DOCKERPINOUT_H
