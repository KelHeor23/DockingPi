#include <iostream>
#include <thread>

#include "MavlinkExchange.h"

MavlinkExchange::MavlinkExchange() {}

int MavlinkExchange::init()
{
    ConnectionResult connection_result = mavsdk->add_any_connection(serialAdress);
    if (connection_result != ConnectionResult::Success) {
        std::cout << "Adding connection failed: " << connection_result << '\n';
        return 0;
    }

    while (mavsdk->systems().size() == 0){
        std::cout << "Systems wait connection" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    auto system = mavsdk->systems().at(0);
    mavlink_passthrough = std::make_unique<MavlinkPassthrough>(system);

    // Подписываемся на сообщения MAVLink типа RC_CHANNELS
    mavlink_passthrough->subscribe_message(MAVLINK_MSG_ID_RC_CHANNELS, [&](const mavlink_message_t& message){
        mavlink_rc_channels_t rc_channels;
        mavlink_msg_rc_channels_decode(&message, &rc_channels);
        if (rc_channels.chancount >= 8) {
            std::cout << "8ch" << std::endl;
            if (rc_channels.chan8_raw > 1600)
                startPin = 1;
            else if (rc_channels.chan8_raw > 1200)
                startPin = 0;
            else
                startPin = -1;
        } else {
            std::cout << "RC Channel 8 is not available." << std::endl;
            return 0;
        }
        return 0;
    });

    return 1;
}

bool MavlinkExchange::getStartPin() const
{
    return startPin;
}
