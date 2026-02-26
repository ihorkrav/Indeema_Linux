

#include <string>
#include <json/json.h>      // THIS IS THE MISSING LINK FOR JSONCPP
#include <serial/serial.h>  // THIS IS THE MISSING LINK FOR SERIAL
#include <unistd.h>
#include <fstream>

struct UartConfig {
    
    std::string port;
    int baudRate;
};

class JsonParser {
public:
    void ParceEcho(const UartConfig& config); // Fixed name to match your .cpp
    bool parse(const std::string& data, Json::Value& root);
    void logMessage(const Json::Value& root);
};

class SerialManager {
private:
    serial::Serial mySerial; // This is the library class

public:
    SerialManager(const UartConfig& config);
    bool isReady();
    void send(const std::string& data);
    std::string receive();
    
    // Moved runEcho here as requested
    Json::Value runEcho(JsonParser& parser); 
};

inline UartConfig loadConfig(const std::string& filename);

