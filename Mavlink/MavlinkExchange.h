/*!
    \file
    \brief Класс инициализирующий обмен с полетником, посредством mavsdk
    \author Князев А.И
*/

#ifndef MAVLINKEXCHANGE_H
#define MAVLINKEXCHANGE_H

#include <mavsdk.h>
#include <mavsdk/system.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/mavlink_passthrough/mavlink_passthrough.h>

using namespace mavsdk;

/*!
    \brief Класс для обмена данными с полетником, посредством mavsdk
*/
class MavlinkExchange
{
    std::unique_ptr<Mavsdk> mavsdk = std::make_unique<Mavsdk>(Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation});
    std::unique_ptr<MavlinkPassthrough> mavlink_passthrough;
public:
    /*!
        \brief Базовый конструктор. Ничего не делает
    */
    MavlinkExchange();

    /*!
        \brief Функция инициализации и запуска обмена
        \return 0 - провал, 1 - успех
    */
    int init();

    /*!
        \brief Функция возвращающая значение пина старта
        \return Возвращает -1, 0, 1 в зависмости от положения тумблера на пульте
    */
    int getStartPin() const;

private:
    int startPin = 0; //< Значение стартового пина

    std::string serialAdress = "serial:///dev/serial4:57600";  //< Serial адресс связи с полетником
};

#endif // MAVLINKEXCHANGE_H
