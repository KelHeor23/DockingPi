/*!
    \file
    \brief Файл, хранящий распиновку
    \author Князев А.И

    Файл, хранящий распиновку устрйоства. Таблицу можно посмотреть непосредсвтенно на устрйостве, введя в терминале команду "gpio readall"
*/
#ifndef DOCKERPINOUT_H
#define DOCKERPINOUT_H

#include <inttypes.h>

/// Пин стрелы
constexpr uint8_t PIN_ROD               = 0;
/// Пин телеги
constexpr uint8_t PIN_CARGO             = 7;
/// Пин сервы правого крюка
constexpr uint8_t PIN_RIGHT_HOOK        = 2;
/// Пин сервы левого крюка
constexpr uint8_t PIN_LEFT_HOOK         = 3;
/// Пин стрела выдвинута
constexpr uint8_t PIN_ROD_EXTENTION     = 12;
/// Пин стрела задвинута
constexpr uint8_t PIN_ROD_RETRACTED     = 13;
/// Пин стыковка завершена
constexpr uint8_t PIN_DOCKING_COMPL     = 14;
/// Пин телега на границе
constexpr uint8_t PIN_CARGO_ON_BORDER   = 22;
/// Пин телега на домашней/стартовой позиции
constexpr uint8_t PIN_CARGO_AT_HOME     = 21;
/// Пин левый крюк активирован
constexpr uint8_t PIN_LEFT_HOOK_ACTIVE  = 23;
/// Пин правый крюк активирован
constexpr uint8_t PIN_RIGHT_HOOK_ACTIVE = 24;
/// Пин замок тележки
constexpr uint8_t PIN_CARGO_LOCK        = 14;


#endif // DOCKERPINOUT_H
