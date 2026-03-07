#pragma once
#include <fstream>
#include <json/json.h>

#include <string>
#include <serial/serial.h>
struct UartConfig {
    std::string port;
    int baudRate;
};
UartConfig loadConfig(const std::string& filename);

class UARTReader {
public:
    UARTReader(const UartConfig& config);

    bool isOpen() const;
    void send(const std::string& data);
    bool hasData();
    std::string readLine();

private:
    serial::Serial serialPort;
};
