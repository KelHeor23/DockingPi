#ifndef MAVLINKEXCHANGE_H
#define MAVLINKEXCHANGE_H

#include <mavsdk.h>
#include <mavsdk/system.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/mavlink_passthrough/mavlink_passthrough.h>

using namespace mavsdk;

namespace MavlinkExchange {

    void handle_rc_channels();
    static mavlink_rc_channels_t rc_channels;

    void initMavlinkExchange();
}


#endif // MAVLINKEXCHANGE_H
