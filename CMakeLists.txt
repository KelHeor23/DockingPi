cmake_minimum_required(VERSION 3.5)

project(DockingPi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MAVSDK REQUIRED)

add_executable(DockingPi main.cpp
    Docker/Docker.h
    Docker/DockerMama.h Docker/DockerMama.cpp
    Docker/DockerPapa.h Docker/DockerPapa.cpp
    Docker/DockerFactory.h
    Docker/DockerPinout.h
    Mavlink/MavlinkExchange.h Mavlink/MavlinkExchange.cpp
    Exchange/I2C/I2CPeripheral.h Exchange/I2C/I2CPeripheral.cpp
    PayloadMechanisms/PCA9685/PCA9685.h PayloadMechanisms/PCA9685/PCA9685.cpp PayloadMechanisms/PCA9685/Constants.h
    PayloadMechanisms/Odometer/Odometer.h PayloadMechanisms/Odometer/Odometer.cpp
    config.h config.cpp
    Exchange/P2P/client.h Exchange/P2P/client.cpp
    Exchange/P2P/server.h Exchange/P2P/server.cpp
    Exchange/P2P/Base.h
)

find_library(WIRINGPI_LIBRARIES wiringPi)
find_package(Threads REQUIRED)

target_link_libraries(DockingPi PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    MAVSDK::mavsdk             #All apps link against mavsdk library
    ${WIRINGPI_LIBRARIES}
    i2c
)

include(GNUInstallDirs)
install(TARGETS DockingPi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
