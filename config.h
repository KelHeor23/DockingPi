#ifndef CONFIG_H
#define CONFIG_H

#include <string>

extern std::string address_g;
extern std::size_t port_g;


/// Переменная определяющая расстоние на которое сдвинется телега для баланса выдвинутой стрелы
constexpr int balance_cargo_g = 45;

#endif // CONFIG_H
