#include "UART_Controller.hpp"

void runEcho(const UartConfig& config) {

    UARTReader uart(config);
    JsonParser parser;

    if (!uart.isOpen()) {
        std::cerr << "Failed to open port\n";
        return;
    }

    std::string testSignal =
        "{\"status\": \"testing\", \"message\": \"Hello UART\"}\n";
    bool var = true;
    while (var) {

        std::cout << "[TX]: Sending signal...\n";
        uart.send(testSignal);

        usleep(500000);

        if (uart.hasData()) {

            std::string received = uart.readLine();

            if (parser.parseMessage(received)) {
                std::cout << "[RX]: Valid JSON received\n";
                var = false;
            }

        } else {
            std::cerr << "[RX]: No data received\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}


void Read_Json(const UartConfig& config, int max_retries = 5) {
    UARTReader uart(config);

    while (true) {

        if (uart.hasData()) {

            std::string received = uart.readLine();

            int r, g, b;

            if (sscanf(received.c_str(), "R:%d G:%d B:%d", &r, &g, &b) == 3) {
                std::cout << "[UART RX] "
                          << "R=" << r
                          << " G=" << g
                          << " B=" << b
                          << std::endl;
            }
            else {
                std::cerr << "[UART RX] Invalid message: " << received << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}