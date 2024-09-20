#include <iostream>
#include <thread>

#include "Mavlink/MavlinkExchange.h"

int main()
{
    while (true) {
        std::cout << "Ch9: " << MavlinkExchange::Instance().getChannelValues(9) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
