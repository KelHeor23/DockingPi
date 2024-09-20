#ifndef MAVLINKEXCHANGE_H
#define MAVLINKEXCHANGE_H

#include <mavsdk.h>
#include <mavsdk/system.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/mavlink_passthrough/mavlink_passthrough.h>

namespace MavlinkExchange {
    using namespace mavsdk;

    mavlink_rc_channels_t rc_channels;

    void handle_rc_channels_message(const mavlink_message_t& message);
    void initMavlinkExchange();
}


#endif // MAVLINKEXCHANGE_H
