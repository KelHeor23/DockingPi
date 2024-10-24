/*!
    \file
    \brief Интерфейс описывающий поведение классов обмена
    \author Князев А.И
*/

#ifndef IEXCHANGE_H
#define IEXCHANGE_H

#include <string>

class IExchange {
    /*!
        \brief Функция отправки сообщения
    */
    virtual void send(std::string msg) = 0;

    /*!
        \brief Функция чтения сообщения
    */
    virtual void read() = 0;
};

#endif // IEXCHANGE_H
