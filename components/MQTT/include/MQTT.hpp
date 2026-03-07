#include <mqtt/async_client.h>
 #include "../../JsonParser/include/JsonParser.hpp" // this is needed to avoid conflict between c++17 and c++14 standards
  

void MQTT_PUBLISH();
mqtt::async_client create_and_connect(const std::string& address, const std::string& id);
void publish_json(mqtt::async_client& client, const std::string& topic, const Json::Value& json_data);
