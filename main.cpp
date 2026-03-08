#include <iostream>
#include "UART_Controller.hpp"
#include "MQTT.hpp"

UartConfig config = loadConfig("../config.json");

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
int main(void){

    
    // UART reading thread
    std::thread uart_thread([]() {
        while (true) {
            Read_Json(config, 5);   // assuming this reads UART and prints data
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