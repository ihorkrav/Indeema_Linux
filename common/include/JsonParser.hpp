

#include <string>
#include <json/json.h>      // THIS IS THE MISSING LINK FOR JSONCPP
#include <serial/serial.h>  // THIS IS THE MISSING LINK FOR SERIAL
#include <unistd.h>
struct UartConfig {
    std::string port;
    int baudRate;
};

class JsonParser {
public:
    void runEcho(const UartConfig& config);
    
private:
    // Now Json::Value will be recognized
    void logMessage(const Json::Value& root);
    bool parse(const std::string& input, Json::Value& output);
};

