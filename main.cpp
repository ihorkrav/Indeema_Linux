#include <iostream>
#include "UART_Controller.hpp"
#include "MQTT.hpp"


int main(void){

    // Map to struct
    //UartConfig config = loadConfig("config.json");
    

    // Task 5: UART Part
   // runEcho(config);

MQTT_PUBLISH();
std::cout << "Publish called" << std::endl;
    return 0;
}