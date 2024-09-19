cmake_minimum_required(VERSION 3.5)

project(DockingPi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MAVSDK REQUIRED)

add_executable(DockingPi main.cpp
    Servo/Servo_SPT5535LV360.h Servo/Servo_SPT5535LV360.cpp
    Servo/Servo_DS3235_270.h Servo/Servo_DS3235_270.cpp
    Servo/Servo.h
)

find_library(WIRINGPI_LIBRARIES wiringPi)

target_link_libraries(DockingPi
    MAVSDK::mavsdk             #All apps link against mavsdk library
    ${WIRINGPI_LIBRARIES}
)

find_library(WIRINGPI_LIBRARIES wiringPi)

include(GNUInstallDirs)
install(TARGETS DockingPi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
