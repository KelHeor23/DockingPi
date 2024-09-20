#include <iostream>
#include <thread>

#include "Mavlink/MavlinkExchange.h"

int main()
{
    while (true) {
        std::cout << "Ch8: " << MavlinkExchange::Instance().getChannelValues(8) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
