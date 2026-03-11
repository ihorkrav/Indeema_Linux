cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)

# Find libserialport from Yocto sysroot
pkg_check_modules(SERIALPORT REQUIRED libserialport)

add_library(UART STATIC
    UART_Reader.cpp
    UART_Controller.cpp
)

target_include_directories(UART
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SERIALPORT_INCLUDE_DIRS}
)

target_link_libraries(UART
    PUBLIC
        JsonParser
        jsoncpp
        ${SERIALPORT_LIBRARIES}
)