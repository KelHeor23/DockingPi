cmake_minimum_required(VERSION 3.5)

project(CountMovementCargo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверка наличия библиотеки wiringPi
find_library(WIRINGPI_LIBRARIES wiringPi)
if(NOT WIRINGPI_LIBRARIES)
    message(FATAL_ERROR "wiringPi library not found!")
endif()

find_package(Threads REQUIRED)

add_executable(CountMovementCargo main.cpp)

target_link_libraries(CountMovementCargo PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    ${WIRINGPI_LIBRARIES}
)
include(GNUInstallDirs)
install(TARGETS CountMovementCargo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
