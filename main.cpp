#include <iostream>
#include <mavsdk.h>
#include <mavsdk/system.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <thread>
#include <mavsdk/plugins/mavlink_passthrough/mavlink_passthrough.h>



using namespace mavsdk;

void print_health(Telemetry::Health health);
void print_rc_status(Telemetry::RcStatus rc_status);

void print_health(Telemetry::Health health)
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

void print_rc_status(Telemetry::RcStatus rc_status)
{
    std::cout << "RC available: " << (rc_status.is_available ? "yes" : "no") << '\n';
    std::cout << "RC available once: " << (rc_status.was_available_once ? "yes" : "no") << '\n';
    std::cout << "RC RSSI: " << rc_status.signal_strength_percent << '\n';
}

 

void handle_rc_channels_message(const mavlink_message_t& message) {
    mavlink_rc_channels_t rc_channels;
    mavlink_msg_rc_channels_decode(&message, &rc_channels);

    // Проверяем, что канал 8 доступен
    if (rc_channels.chancount >= 8) {
        std::cout << "RC Channel 8: " << rc_channels.chan8_raw << std::endl;
    } else {
        std::cout << "RC Channel 8 is not available." << std::endl;
    }
}

int main()
{
    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation}};

    // ConnectionResult ret = mavsdk.add_udp_connection();
    ConnectionResult connection_result = mavsdk.add_any_connection("serial:///dev/serial0:57600");
    if (connection_result != ConnectionResult::Success) {
        std::cout << "Adding connection failed: " << connection_result << '\n';
        return 0;
    }

    while (mavsdk.systems().size() == 0){
        std::cout << "Systems wait connection" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    auto system = mavsdk.systems().at(0);

    auto telemetry = std::make_shared<Telemetry>(system);

    telemetry->subscribe_health([](Telemetry::Health health) { print_health(health); });
    telemetry->subscribe_rc_status([](Telemetry::RcStatus rc_status) { print_rc_status(rc_status); });
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "tel: " << telemetry->position();

    
    auto mavlink_passthrough = MavlinkPassthrough(system);
    // MavlinkPassthrough mavlink_passthrough(system.value());

    // Подписываемся на сообщения MAVLink типа RC_CHANNELS
    mavlink_passthrough.subscribe_message(MAVLINK_MSG_ID_RC_CHANNELS, handle_rc_channels_message);

    // Ждем некоторое время, чтобы получить сообщения
    std::this_thread::sleep_for(std::chrono::seconds(10));

}
