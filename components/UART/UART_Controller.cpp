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

        sleep(2);
    }
}



