/*!
    \file
    \brief Простая фабрика создающая объекты типов стыковки
    \author Князев А.И
*/

#ifndef DOCKERFACTORY_H
#define DOCKERFACTORY_H

#include <memory>

#include "DockerMama.h"
#include "DockerPapa.h"

std::string types_g = "Mama Papa";

/*!
    \brief Виды стыковки/устройства
*/
enum Dockers {
    Mama,
    Papa
};

/*!
    \brief Простая фабрика создающая объекты типов стыковки
*/
class DockerFactory
{
public:
    /*!
    \brief  Функция фабрики создающая объекты модуля стыковки
    \param[in] type тип необходимого объекта
    \return Возвращает unique_ptr созданного объекта
    */
    std::unique_ptr<Docker> makeDocker(Dockers type) {
        switch(type){
        case Mama:
            return std::make_unique<DockerMama>();
        case Papa:
            return std::make_unique<DockerPapa>();
        default:
            return nullptr;
        }
    }
};

#endif // DOCKERFACTORY_H
