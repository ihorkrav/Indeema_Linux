#include "UART_Reader.hpp"


UARTReader::UARTReader(const UartConfig& config)
{
    if (sp_get_port_by_name(config.port.c_str(), &port) != SP_OK)
        throw std::runtime_error("Failed to get serial port");

    if (sp_open(port, SP_MODE_READ_WRITE) != SP_OK)
        throw std::runtime_error("Failed to open serial port");

    sp_set_baudrate(port, config.baudRate);
    sp_set_bits(port, 8);
    sp_set_parity(port, SP_PARITY_NONE);
    sp_set_stopbits(port, 1);
    sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);
}

UARTReader::~UARTReader()
{
    if (port) {
        sp_close(port);
        sp_free_port(port);
    }
}

bool UARTReader::isOpen() const
{
    return port != nullptr;
}

void UARTReader::send(const std::string& data)
{
    if (!port)
        throw std::runtime_error("Serial port not open");

    sp_blocking_write(port, data.c_str(), data.size(), 1000);
}

bool UARTReader::hasData()
{
    if (!port)
        return false;

    return sp_input_waiting(port) > 0;
}

std::string UARTReader::readLine()
{
    if (!port)
        throw std::runtime_error("Serial port not open");

    std::string result;
    char ch;

    while (true)
    {
        int bytes = sp_blocking_read(port, &ch, 1, 1000);

        if (bytes > 0)
        {
            if (ch == '\n')
                break;

            result += ch;
        }
        else
        {
            break;
        }
    }

    return result;
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