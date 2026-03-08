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
    JsonParser parser;

    int attempts = 0;
    bool success = false;

    // Keep trying until we succeed or hit the retry limit
    while (attempts < max_retries && !success) {
        if (uart.hasData()) {
            std::string received = uart.readLine();

            if (parser.parseMessage(received)) {
                std::cout << "[RX]: Valid JSON received\n";
               
                
            } else {
                std::cerr << "[RX]: Received malformed JSON, retrying...\n";
            }
        } else {
            std::cerr << "[RX]: Timeout, no data. Attempt " << (attempts + 1) << "/" << max_retries << "\n";
        }

        attempts++;
        if (!success) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    if (!success) {
        std::cerr << "[RX]: Failed to receive valid data after " << max_retries << " attempts.\n";
    }
}




