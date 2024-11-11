cmake_minimum_required(VERSION 3.5)

project(DockingPi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MAVSDK REQUIRED)

add_executable(DockingPi main.cpp
    Servo/Servo_SPT5535LV360.h Servo/Servo_SPT5535LV360.cpp
    Servo/Servo_DS3235_270.h Servo/Servo_DS3235_270.cpp
    Servo/Servo.h
    Docker/Docker.h
    Docker/DockerMama.h Docker/DockerMama.cpp
    Docker/DockerPapa.h Docker/DockerPapa.cpp
    Docker/DockerFactory.h
    Docker/DockerPinout.h
    Mavlink/MavlinkExchange.h Mavlink/MavlinkExchange.cpp

    Exchange/Client.h Exchange/Client.cpp
    Exchange/Server.h Exchange/Server.cpp
    Exchange/Config.h
    Exchange/IExchange.h
    Exchange/Config.cpp
    Exchange/I2C/I2CPeripheral.h Exchange/I2C/I2CPeripheral.cpp
    Servo/PCA9685/PCA9685.h Servo/PCA9685/PCA9685.cpp Servo/PCA9685/Constants.h
)

find_library(WIRINGPI_LIBRARIES wiringPi)

target_link_libraries(DockingPi
    ncurses
    MAVSDK::mavsdk             #All apps link against mavsdk library
    ${WIRINGPI_LIBRARIES}
    i2c
)

find_library(WIRINGPI_LIBRARIES wiringPi)

include(GNUInstallDirs)
install(TARGETS DockingPi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
