cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#find_package(REQUIRED jsoncpp)

add_library(UART STATIC
    UART_Reader.cpp
    UART_Controller.cpp
)

target_include_directories(UART
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(UART
    PUBLIC
    JsonParser
    jsoncpp
)


