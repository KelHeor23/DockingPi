#include <iostream>
#include <mavsdk.h>
#include <mavsdk/system.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

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

int main()
{
    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation}};

    ConnectionResult ret = mavsdk.add_any_connection("udpin://0.0.0.0:14540");

    auto system = mavsdk.systems().at(0);

    auto telemetry = std::make_shared<Telemetry>(system);

    telemetry->subscribe_health([](Telemetry::Health health) { print_health(health); });
    telemetry->subscribe_rc_status([](Telemetry::RcStatus rc_status) { print_rc_status(rc_status); });
}
