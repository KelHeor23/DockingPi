#ifndef MAVLINKEXCHANGE_H
#define MAVLINKEXCHANGE_H

#include <mavsdk.h>
#include <mavsdk/system.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/mavlink_passthrough/mavlink_passthrough.h>

using namespace mavsdk;

class MavlinkExchange
{
    std::unique_ptr<Mavsdk> mavsdk = std::make_unique<Mavsdk>(Mavsdk::Configuration{Mavsdk::ComponentType::GroundStation});
    std::unique_ptr<MavlinkPassthrough> mavlink_passthrough;
public:
    MavlinkExchange();
    int init();

    bool getStartPin() const;

private:
    int startPin = 0;

    std::string serialAdress = "serial:///dev/serial0:115200";
};

#endif // MAVLINKEXCHANGE_H
