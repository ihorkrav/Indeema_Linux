#include "JsonParser.hpp"
#include "UART_Reader.hpp"
#include <iostream>
#include <thread>
#include <chrono>
void runEcho(const UartConfig& config);
void Read_Json(const UartConfig& config, int max_retries);
