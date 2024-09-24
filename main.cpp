#include <iostream>
#include <thread>
#include <unistd.h>
#include <mavsdk.h>
#include <mavsdk/system.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/mavlink_passthrough/mavlink_passthrough.h>

#include "Docker/DockerFactory.h"

using namespace mavsdk;

// Execution frequency
void exec_freq(){
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

int main(int argc, char *argv[])
{
    DockerFactory factory;
    std::unique_ptr<Docker> docker;
    bool startPin = 0;
    /* Read params and running fabric*/
    //-----------------------------------------------------------------------------------------------

    {
        if (argc != 2) {
            std::cerr << "Please write type of drone. Types: " << types_g << std::endl;
            return 0;
        }

        if (wiringPiSetup() == -1) {
            std::cerr << "Ошибка инициализации WiringPi." << std::endl;
            return 0;
        }

        std::string type(argv[1]);

        if (type.compare("Papa") == 0){
            docker = factory.makeDocker(Dockers::Papa);
        } else if (type.compare("Mama") == 0){
            docker = factory.makeDocker(Dockers::Mama);
        } else {
            std::cerr << "unknow type of drone. Types: " << types_g << std::endl;
            return 0;
        }

        std::cout << "The program is running for type" << type << std::endl;
    }
    //-----------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------------
    /* Connect to Mavsdk and handle to rcChannels*/
    //-----------------------------------------------------------------------------------------------

    std::unique_ptr<Mavsdk> mavsdk = std::make_unique<Mavsdk>(Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation});
    std::unique_ptr<MavlinkPassthrough> mavlink_passthrough;

    {
        std::cout << "docking begin" << std::endl;

        ConnectionResult connection_result = mavsdk->add_any_connection("serial:///dev/serial0:115200");
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
                if (rc_channels.chan8_raw > 1600)
                    startPin = 1;
                else
                    startPin = 0;
            } else {
                std::cout << "RC Channel 8 is not available." << std::endl;
                return 0;
            }
            return 1;
        });
    }
    //-----------------------------------------------------------------------------------------------

    while (true) {
        if (startPin)
            docker->docking();
        else
            docker->undocking();
        exec_freq();
    }
    return 0;
}
