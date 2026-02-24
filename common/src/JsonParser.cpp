#include "JsonParser.hpp"
#include <iostream>

void JsonParser::runEcho(const UartConfig& config) {
    try {
        serial::Serial mySerial(config.port, config.baudRate, 
                                serial::Timeout::simpleTimeout(1000));

        if (!mySerial.isOpen()) {
            std::cerr << "Failed to open port: " << config.port << std::endl;
            return;
        }

        std::cout << "UART Loopback Test Active on " << config.port << std::endl;

        // 1. Prepare a signal (JSON message) to send
        std::string testSignal = "{\"status\": \"testing\", \"message\": \"Hello UART\"}\n";

        while (true) {
            // 2. Send the signal through TX
            std::cout << "\n[TX]: Sending signal..." << std::endl;
            mySerial.write(testSignal);

            // 3. Wait a moment for the hardware to process/loop back
            // (Small sleep prevents saturating the CPU)
            usleep(500000); // 500ms

            // 4. Check if signal was received on RX
            if (mySerial.available()) {
                std::string receivedData = mySerial.readline(65536, "\n");
                
                // 5. Parse and Validate
                Json::Value root;
                if (this->parse(receivedData, root)) {
                    std::cout << "[RX]: Success! Received valid JSON." << std::endl;
                    this->logMessage(root);
                } else {
                    std::cerr << "[RX]: Received data, but JSON parsing failed!" << std::endl;
                }
            } else {
                std::cerr << "[RX]: No data received. Check your TX-RX jumper wire!" << std::endl;
            }

            // Wait before next test cycle
            sleep(2); 
        }
    } catch (const std::exception& e) {
        std::cerr << "Serial Error: " << e.what() << std::endl;
    }
}

bool JsonParser::parse(const std::string& input, Json::Value& output) {
    Json::CharReaderBuilder builder;
    auto reader = builder.newCharReader();
    std::string errs;
    return reader->parse(input.c_str(), input.c_str() + input.size(), &output, &errs);
}

void JsonParser::logMessage(const Json::Value& root) {
    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, root);
    std::cout << "[LOG]: " << jsonString << std::endl;
}