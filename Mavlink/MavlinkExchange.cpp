#include <iostream>
#include <thread>

#include "MavlinkExchange.h"

void MavlinkExchange::initMavlinkExchange()
{
    std::thread handleRcChannels(handle_rc_channels);
    handleRcChannels.detach();
}

void MavlinkExchange::handle_rc_channels()
{
    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation}};

    // ConnectionResult ret = mavsdk.add_udp_connection();
    ConnectionResult connection_result = mavsdk.add_any_connection("serial:///dev/serial0:57600");
    if (connection_result != ConnectionResult::Success) {
        std::cout << "Adding connection failed: " << connection_result << '\n';
        return;
    }

    while (mavsdk.systems().size() == 0){
        std::cout << "Systems wait connection" << std::endl;

    }

    auto system = mavsdk.systems().at(0);

    auto mavlink_passthrough = MavlinkPassthrough(system);

    // Подписываемся на сообщения MAVLink типа RC_CHANNELS
    mavlink_passthrough.subscribe_message(MAVLINK_MSG_ID_RC_CHANNELS, [](const mavlink_message_t& message){mavlink_msg_rc_channels_decode(&message, &MavlinkExchange::rc_channels);});

    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
