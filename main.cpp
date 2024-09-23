#include <iostream>
#include <unistd.h>
#include <mavsdk.h>
#include <mavsdk/system.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <thread>
#include <mavsdk/plugins/mavlink_passthrough/mavlink_passthrough.h>

using namespace mavsdk;

// Execution frequency
void exec_freq(){
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

int main()
{
    bool startPin = 0;

    Mavsdk mavsdk{Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation}};
    std::cout << "docking begin" << std::endl;
#include "Servo/Servo.h"

    if (wiringPiSetup() == -1) {
        std::cerr << "Ошибка инициализации WiringPi." << std::endl;
        return 1;
    }
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
    auto mavlink_passthrough = MavlinkPassthrough(system);

    // Подписываемся на сообщения MAVLink типа RC_CHANNELS
    mavlink_passthrough.subscribe_message(MAVLINK_MSG_ID_RC_CHANNELS, [&](const mavlink_message_t& message){
        mavlink_rc_channels_t rc_channels;
        mavlink_msg_rc_channels_decode(&message, &rc_channels);
        if (rc_channels.chancount >= 8) {
            if (rc_channels.chan8_raw > 1600)
                startPin = 1;
            else
                startPin = 0;
        } else {
            std::cout << "RC Channel 8 is not available." << std::endl;
            return 0;
        }
    });

    while (true) {
        if (startPin)
            std::cout << "Start" << std::endl;
        else
            std::cout << "Stop" << std::endl;
        exec_freq();
    }
    return 0;
}
