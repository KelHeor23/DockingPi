/*!
    \file
    \brief Класс описывающий модуль стыковки для устройства Papa
    \author Князев А.И
*/
#ifndef DOCKERPAPA_H
#define DOCKERPAPA_H

#include "Docker.h"

#include "../Exchange/P2P/client.h"

/*!
    \brief Класс описывающий модуль стыковки для устройства Papa
*/
class DockerPapa : public Docker
{
public:
    /*!
        \brief Конструктор объекта. Ничего не делает
    */
    DockerPapa();
    ~DockerPapa(){}

    /*!
        \brief Функция работы модуля стыковки. Запускаемая в бесконечном цикле.
    */
    void docking() override;

    /*!
        \brief Функция расстыковки. Запускаемая в бесконечном цикле.
    */
    void undocking() override;

    /*!
        \brief Функция прокидывающая вызывающая connect в client
    */
    void connect()      override;

private:

    /*!
        \brief Фукнция выдвижения стрелы
    */
    void rodExtension();

    /*!
        \brief Фукнция возврата стрелы
    */
    void rodRetraction();

    /*!
        \brief Функция стягивания дронов
    */
    void pullingUp();

    /*!
        \brief Функция выдвижения стрелы, для расталкивания двух дронов
    */
    void pushAway();

    /*!
        \brief Функция передачи телеги
    */
    void cargoTransfer();

    /*!
        \brief Функция плавного завершения передачи телеги
    */
    void cargoTransferEnding();

    /*!
        \brief Функция дергающая обмен с мамой и актуализирующая сообщения
    */
    void mamaExchange();

private:    
    int cargoPosStart = 0;
    bool firstFlag = true;

    Client clientPapa;
};

#endif // DOCKERPAPA_H
