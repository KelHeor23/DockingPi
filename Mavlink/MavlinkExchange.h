#ifndef MAVLINKEXCHANGE_H
#define MAVLINKEXCHANGE_H

#include <mavsdk.h>
#include <mavsdk/system.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/mavlink_passthrough/mavlink_passthrough.h>

namespace Channels {
    static mavlink_rc_channels_t m_rc_channels;
    static uint16_t m_ch8;
};

class MavlinkExchange
{
public:

    static MavlinkExchange& Instance(){
        static MavlinkExchange instance;
        return instance;
    }

    void printTelemInfo();                  // Вывод общей информации по телеметрии
    uint16_t getChannelValues(uint8_t ch);  // Вывод значения какнала
private:
    MavlinkExchange();
    void print_health(mavsdk::Telemetry::Health health);
    void print_rc_status(mavsdk::Telemetry::RcStatus rc_status);
    static void handle_rc_channels_message(const mavlink_message_t& message);   // Функция собирающая сообщнеия по rc каналам

private:
    std::shared_ptr<mavsdk::Telemetry> telemetry;

};

#endif // MAVLINKEXCHANGE_H
