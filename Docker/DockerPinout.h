#ifndef DOCKERPINOUT_H
#define DOCKERPINOUT_H

#include <inttypes.h>

//wPi. in terminal use command: gpio readall
constexpr uint8_t PIN_ROD           = 7;
constexpr uint8_t PIN_CARGO         = 0;
constexpr uint8_t PIN_RIGHT_HOOK    = 2;
constexpr uint8_t PIN_LEFT_HOOK     = 3;
constexpr uint8_t PIN_ROD_EXTENTION = 12;
constexpr uint8_t PIN_ROD_RETRACTED = 13;
constexpr uint8_t PIN_DOCKING_COMPL = 14;


#endif // DOCKERPINOUT_H
