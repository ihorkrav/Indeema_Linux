
#pragma once
#include <json/json.h>      
#include <serial/serial.h>  
#include <unistd.h>
#include <iostream>

class JsonParser {
public:
    // Now Json::Value will be recognized
    void logMessage(const Json::Value& root);
    bool parse(const std::string& input, Json::Value& output);
    bool parseMessage(const std::string& message);
};

std::string make_rgb_json(int r, int g, int b);