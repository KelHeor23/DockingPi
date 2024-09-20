#include <iostream>
#include <thread>

#include "Mavlink/MavlinkExchange.h"

int main()
{
    MavlinkExchange::initMavlinkExchange();

    while (true) {
        std::cout << "Ch8: " << MavlinkExchange::rc_channels.chan8_raw << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
