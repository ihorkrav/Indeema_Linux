set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Important for binary compatibility

find_package(PahoMqttCpp REQUIRED)

add_library(MQTT STATIC MQTT.cpp)

target_include_directories(MQTT
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include
)

# Link against the Paho MQTT C++ library
target_link_libraries(MQTT PRIVATE PahoMqttCpp::paho-mqttpp3 jsoncpp)