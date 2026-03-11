#include <iostream>
#include <libgen.h> 
#include <unistd.h>
#include <limits.h>
#include "UART_Controller.hpp"
#include "MQTT.hpp"


int getValidColorValue(const std::string& colorName) {
    int value;
    while (true) {
        std::cout << "Enter " << colorName << " (0-255): ";
        if (std::cin >> value) {
            // Input was a number, now check the range
            if (value >= 0 && value <= 255) {
                return value;
            } else {
                std::cout << "Error: Value must be between 0 and 255." << std::endl;
            }
        } else {
            // Input failed (e.g., user typed text)
            std::cout << "Error: Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error flag on cin
            // Discard the bad input from the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void get_rgb_input(int* r, int* g, int* b) {
    *r = getValidColorValue("RED");
    *g = getValidColorValue("GREEN");
    *b = getValidColorValue("BLUE");
    
    std::cout << "RGB set to: (" << *r << ", " << *g << ", " << *b << ")" << std::endl;
}

std::string getExecutableDir() {
    char buffer[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
    if (count != -1) {
        return std::string(dirname(buffer));
    }
    return "."; // Fallback to current directory
}
int main(void){

    std::string configPath = getExecutableDir() + "/config.json";
    
    // Load the config
    UartConfig config = loadConfig(configPath.c_str());
    // UART reading thread
    std::thread uart_thread([&config]() {
    while (true) {
        Read_Json(config, 5);
    }
});

    // Main thread handles user input + MQTT
    while (true) {
        int r, g, b;

        get_rgb_input(&r, &g, &b);

        MQTT_PUBLISH(r, g, b);

    }

    uart_thread.join();
    return 0;
}