cmake_minimum_required(VERSION 3.5)

project(DockingPi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MAVSDK REQUIRED)

add_executable(DockingPi main.cpp
    Mavlink/MavlinkExchange.h Mavlink/MavlinkExchange.cpp)

target_link_libraries(DockingPi
    MAVSDK::mavsdk             #All apps link against mavsdk library
)

find_library(WIRINGPI_LIBRARIES wiringPi)

include(GNUInstallDirs)
install(TARGETS DockingPi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
