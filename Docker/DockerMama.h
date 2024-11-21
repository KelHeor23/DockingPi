/*!
    \file
    \brief Класс описывающий модуль стыковки для устройства Mama
    \author Князев А.И
*/
#ifndef DOCKERMAMA_H
#define DOCKERMAMA_H

#include "Docker.h"

#include "../Exchange/Server.h"

/*!
    \brief Класс описывающий модуль стыковки для устроЙства Mama
*/
class DockerMama : public Docker
{
public:
    /*!
        \brief Конструктор объекта. Возвращает сервый крюков в нейтральное положение
    */
    DockerMama();
    ~DockerMama(){}

    /*!
        \brief Функция работы модуля стыковки. Запускаемая в бесконечном цикле.
    */
    void docking()      override;

    /*!
        \brief Функция расстыковки. Запускаемая в бесконечном цикле.
    */
    void undocking()    override;

    /*!
        \brief Функция прокидывающая вызывающая connect в server
    */
    void connect()      override;

private:

    /**
        \brief Функция закрытия крюков
    */
    void lockingHooks();

    /*!
        \brief Функция плавного старта/подготовки к приему телеги
    */;
    void cargoTransferBegin();

    /*!
        \brief Функция плавного завершения приёма телеги
    */
    void cargoTransferEnding();

private:
    Server server;
};

#endif // DOCKERMAMA_H
