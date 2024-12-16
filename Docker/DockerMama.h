/*!
    \file
    \brief Класс описывающий модуль стыковки для устройства Mama
    \author Князев А.И
*/
#ifndef DOCKERMAMA_H
#define DOCKERMAMA_H

#include "Docker.h"

#include "../Exchange/P2P/server.h"

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

    /*!
        \brief Функция остановки сервы телеги
    */
    void cargoStop() override {
        cargoLock();
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 + 0x20);
    }

    /*!
        \brief Функция паузы стыковки. Запускаемая в бесконечном цикле.
    */
    void stop() override{
        pca.set_pwm(PCA9685::PIN_ROD, 0, PCA9685::ms1500);
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 + 0x20);
        cargoLock();
        odometerCargo.setCurState(0);
    }

    /*!
        \brief Функция вращения сервы телеги по часовй стрелке
    */
    void cargoCV() override{
        cargoUnLock();
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 + PCA9685::step * 4);
    }

    /*!
        \brief Функция вращения сервы телеги против часовй стрелки
    */
    void cargoCCV() override{
        cargoUnLock();
        pca.set_pwm(PCA9685::PIN_CARGO, 0, PCA9685::ms1500 - PCA9685::step);
    }


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

    /*!
        \brief Функция дергающая обмен с папой и актуализирующая сообщения
    */
    void papaExchange();

private:
    Server serverMama;
};
#endif // DOCKERMAMA_H
