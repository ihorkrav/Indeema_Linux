#include "JsonParser.hpp"

bool JsonParser::parseMessage(const std::string& message) {
    Json::Value root;

    if (!parse(message, root)) {
        std::cerr << "Invalid JSON\n";
        return false;
    }

    logMessage(root);
    return true;
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

std::string make_rgb_json(int r, int g, int b){
    Json::Value rgb_data;
    rgb_data["red"] = r;
    rgb_data["green"] = g;
    rgb_data["blue"] = b;
    Json::StreamWriterBuilder writer;
    std::string payload = Json::writeString(writer, rgb_data);
    return payload;
}