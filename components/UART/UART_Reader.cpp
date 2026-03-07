#include "UART_Reader.hpp"


UARTReader::UARTReader(const UartConfig& config)
    : serialPort(config.port, config.baudRate, 
                 serial::Timeout::simpleTimeout(1000)) {}

// Method implementations
bool UARTReader::isOpen() const {
    return serialPort.isOpen();
}

void UARTReader::send(const std::string& data) {
    serialPort.write(data);
}

bool UARTReader::hasData() {
    return serialPort.available() > 0;
}

std::string UARTReader::readLine() {
    return serialPort.readline(65536, "\n");
}

UartConfig loadConfig(const std::string& filename)
{
    std::ifstream file(filename);
    UartConfig config;

    if (!file.is_open())
        throw std::runtime_error("Unable to open config file!");

    Json::Value root;
    file >> root;

    if (root.isMember("uart_port"))
        config.port = root["uart_port"].asString();
    else
        config.port = "/dev/ttyUSB0";

    if (root.isMember("baud_rate"))
        config.baudRate = root["baud_rate"].asInt();
    else
        config.baudRate = 115200;

    return config;
}