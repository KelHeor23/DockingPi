#include <iostream>
#include <thread>

#include "MavlinkExchange.h"

void MavlinkExchange::initMavlinkExchange(){
    mavsdk = std::make_unique<Mavsdk>(Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation});

    ConnectionResult connection_result = mavsdk->add_any_connection("serial:///dev/serial0:57600");

    if (connection_result != ConnectionResult::Success) {
        std::cout << "Adding connection failed: " << connection_result << '\n';
        return;
    }

    while (mavsdk->systems().size() == 0){
        std::cout << "Systems wait connection" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    system = mavsdk->systems().at(0);

    mavlink_passthrough = std::make_unique<MavlinkPassthrough>(system);

    mavlink_passthrough->subscribe_message(MAVLINK_MSG_ID_RC_CHANNELS, [=](const mavlink_message_t& message){mavlink_msg_rc_channels_decode(&message, &rc_channels);});
}
