#ifndef DOCKERPINOUT_H
#define DOCKERPINOUT_H

#include <inttypes.h>

//wPi. in terminal use command: gpio readall
constexpr uint8_t PIN_ROD               = 7;
constexpr uint8_t PIN_CARGO             = 0;
constexpr uint8_t PIN_RIGHT_HOOK        = 2;
constexpr uint8_t PIN_LEFT_HOOK         = 3;
constexpr uint8_t PIN_ROD_EXTENTION     = 12;
constexpr uint8_t PIN_ROD_RETRACTED     = 13;
constexpr uint8_t PIN_DOCKING_COMPL     = 14;
constexpr uint8_t PIN_CARGO_ON_BORDER   = 21;
constexpr uint8_t PIN_CARGO_AT_HOME     = 22;
constexpr uint8_t PIN_LEFT_HOOK_ACTIVE  = 23;
constexpr uint8_t PIN_RIGHT_HOOK_ACTIVE = 24;


#endif // DOCKERPINOUT_H
