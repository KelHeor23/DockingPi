#include <iostream>
#include <thread>

#include "MavlinkExchange.h"


MavlinkExchange::MavlinkExchange() {
    mavsdk::Mavsdk mavsdk{mavsdk::Mavsdk::Configuration{mavsdk::Mavsdk::ComponentType::GroundStation}};

    mavsdk::ConnectionResult connection_result = mavsdk.add_any_connection("serial:///dev/serial0:57600");
    if (connection_result != mavsdk::ConnectionResult::Success) {
        std::cout << "Adding connection failed: " << connection_result << '\n';
        throw "Abbort operation";
    }

    while (mavsdk.systems().size() == 0){
        std::cout << "Systems wait connection" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    auto system = mavsdk.systems().at(0);
    auto mavlink_passthrough = mavsdk::MavlinkPassthrough(system);
    mavlink_passthrough.subscribe_message(MAVLINK_MSG_ID_RC_CHANNELS, handle_rc_channels_message);

    std::make_shared<mavsdk::Telemetry>(system);
    telemetry->subscribe_health([this](mavsdk::Telemetry::Health health){print_health(health);});
    telemetry->subscribe_rc_status([this](mavsdk::Telemetry::RcStatus rc_status){print_rc_status(rc_status);});
}


void MavlinkExchange::print_health(mavsdk::Telemetry::Health health)
{
    std::cout << "Got health: " << '\n';

    std::cout << "Gyro calibration:  " << (health.is_gyrometer_calibration_ok ? "ok" : "not ok")
              << '\n';
    std::cout << "Accel calibration: " << (health.is_accelerometer_calibration_ok ? "ok" : "not ok")
              << '\n';
    std::cout << "Mag calibration:   " << (health.is_magnetometer_calibration_ok ? "ok" : "not ok")
              << '\n';
    std::cout << "Local position:    " << (health.is_local_position_ok ? "ok" : "not ok") << '\n';
    std::cout << "Global position:   " << (health.is_global_position_ok ? "ok" : "not ok") << '\n';
    std::cout << "Home position:     " << (health.is_home_position_ok ? "ok" : "not ok") << '\n';
}

void MavlinkExchange::print_rc_status(mavsdk::Telemetry::RcStatus rc_status)
{
    std::cout << "RC available: " << (rc_status.is_available ? "yes" : "no") << '\n';
    std::cout << "RC available once: " << (rc_status.was_available_once ? "yes" : "no") << '\n';
    std::cout << "RC RSSI: " << rc_status.signal_strength_percent << '\n';
}

void MavlinkExchange::handle_rc_channels_message(const mavlink_message_t& message) {

    mavlink_msg_rc_channels_decode(&message, &Channels::m_rc_channels);

    // Проверяем, что канал 8 доступен
    if (Channels::m_rc_channels.chancount >= 8)
        Channels::m_ch8 = Channels::m_rc_channels.chan8_raw;
    else
        Channels::m_ch8 = 0;

}

uint16_t MavlinkExchange::getChannelValues(uint8_t ch)
{
    switch(ch){
    case 8:
        return Channels::m_ch8;
    default:
        return 0;
    }
    return 0;
}

