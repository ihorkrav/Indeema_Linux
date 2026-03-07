#include "MQTT.hpp"
const std::string SERVER_ADDRESS("mqtt://broker.hivemq.com:1883");
const std::string TOPIC("linux_connection/test");

// 1. Connection logic remains the same
void connect_client(mqtt::async_client& client) {
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);
    client.connect(connOpts)->wait();
}

// 2. Updated to handle Json::Value
void publish_json(mqtt::async_client& client, const std::string& topic, std::string json_data) {
    // Serialize JSON object to string
    
    
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, json_data, 1, false);
    client.publish(pubmsg)->wait();
    std::cout << "Published JSON: " << json_data << std::endl;
}

// 3. Orchestration function with RGB input
void MQTT_PUBLISH() {
    int r, g, b;
    std::cout << "Enter RGB values (0-255) separated by spaces: ";
    if (!(std::cin >> r >> g >> b)) {
        std::cerr << "Invalid input." << std::endl;
        return;
    }

    // Build the JSON object
    std::string data = make_rgb_json(r, g, b);

    auto now = std::chrono::system_clock::now().time_since_epoch().count();
    std::string client_id = "cpp_pub_" + std::to_string(now);

    mqtt::async_client client(SERVER_ADDRESS, client_id);        
    try {
        connect_client(client);
        publish_json(client, TOPIC, data);
        client.disconnect()->wait();;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
    }
}