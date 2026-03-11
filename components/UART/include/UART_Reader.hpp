#pragma once

#include <fstream>
#include <string>
#include <json/json.h>

#include <libserialport.h>
#include <stdexcept>
#include <vector>

struct UartConfig {
    std::string port;
    int baudRate;
};

UartConfig loadConfig(const std::string& filename);

class UARTReader {
public:
    UARTReader(const UartConfig& config);
    ~UARTReader();

    bool isOpen() const;
    void send(const std::string& data);
    bool hasData();
    std::string readLine();

private:
    struct sp_port* port = nullptr;
};