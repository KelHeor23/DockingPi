#ifndef CONFIG_H
#define CONFIG_H

#include <string>

/// IP Адресс устрйоства мама
extern std::string address_g;

/// порт устрйоства мама
extern std::size_t port_g;


/// Переменная определяющая расстоние на которое сдвинется телега для баланса выдвинутой стрелы
extern int balance_cargo_g;

/// Переменная определяющая расстоние на котором считаем, что телега покинула папу
extern int cargoLeftPapa;

/// Переменная определяющая расстоние на котором считаем, что телега начала переходить к маме
extern int cargoOnBorder;

/// Переменная определяющая расстоние от хвоста мамы до точки баланса мамы
extern int cargoAtHome;

#endif // CONFIG_H
