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
    virtual void sendMsg(std::string msg) = 0;

    /*!
        \brief Функция чтения сообщения
    */
    virtual std::string read() = 0;

    /*!
        \brief Функция устанавливающая соединения
    */
    virtual bool connect(std::string address, std::size_t port) = 0;
};

#endif // IEXCHANGE_H
