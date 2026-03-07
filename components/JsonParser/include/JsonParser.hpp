
#pragma once
#include <json/json.h>      // THIS IS THE MISSING LINK FOR JSONCPP
#include <serial/serial.h>  // THIS IS THE MISSING LINK FOR SERIAL
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