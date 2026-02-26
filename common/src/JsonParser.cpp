#include "JsonParser.hpp"
#include <iostream>
#include <unistd.h>

// --- SerialManager Implementation ---

SerialManager::SerialManager(const UartConfig& config) 
    : mySerial(config.port, config.baudRate, serial::Timeout::simpleTimeout(1000)) {}

bool SerialManager::isReady() { 
    return mySerial.isOpen(); 
}

void SerialManager::send(const std::string& data) {
    mySerial.write(data);
}

std::string SerialManager::receive() {
    if (mySerial.available()) {
        return mySerial.readline(65536, "\n");
    }
    return "";
}

Json::Value SerialManager::runEcho(JsonParser& parser) {
    if (!mySerial.isOpen()) {
        std::cerr << "Port failure." << std::endl;
        return Json::Value(); // Return empty object instead of 'return;'
    }

    std::string testSignal = "{\"status\": \"testing\", \"message\": \"Hello UART\"}\n";

    while (true) {
        std::cout << "[TX]: Sending..." << std::endl;
        mySerial.write(testSignal);
        usleep(500000); 

        std::string receivedData = receive();
        if (!receivedData.empty()) {
            Json::Value root;
            if (parser.parse(receivedData, root)) {
                std::cout << "[RX]: Valid JSON received." << std::endl;
                return root; // Exits loop on success
            }
        } else {
            std::cerr << "[RX]: No data. Check jumper!" << std::endl;
        }
        sleep(2); 
    }
}

// --- JsonParser Implementation ---

void JsonParser::ParceEcho(const UartConfig& config) {
    try {
        SerialManager manager(config);
        if (manager.isReady()) {
            Json::Value result = manager.runEcho(*this);
            logMessage(result);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool JsonParser::parse(const std::string& data, Json::Value& root) {
    Json::CharReaderBuilder builder;
    std::string errs;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    return reader->parse(data.c_str(), data.c_str() + data.size(), &root, &errs);
}

void JsonParser::logMessage(const Json::Value& root) {
    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, root);
    std::cout << "[LOG]: " << jsonString << std::endl;
}


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