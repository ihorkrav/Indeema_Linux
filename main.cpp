#include <libserial/SerialPort.h> // Include the serial library
#include <iostream>
#include "JsonParser.hpp"
#include <json/json.h>

UartConfig loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    Json::Value root;
    UartConfig config;

    if (file.is_open()) {
        file >> root;

        // Populate struct members
        // Syntax: root.get("key", default_value).asType()
        config.port = root.get("uart_port", "/dev/ttyUSB0").asString();
        config.baudRate = root.get("baud_rate", 115200).asInt();        
    } else {
        throw std::runtime_error("Unable to open config file!");
    }

    return config;
}
int main(void){
    // Map to struct
    UartConfig config = loadConfig("config.json");
    

    // Task 5: UART Part
    JsonParser processor;
    for(;;)
        processor.ParceEcho(config);



    return 0;
}