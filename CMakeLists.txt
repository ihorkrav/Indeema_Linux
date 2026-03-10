project(Indeema_Linux)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(components)

add_executable(Indeema_Linux main.cpp)

target_link_libraries(Indeema_Linux
    PRIVATE
    UART
    MQTT
    JsonParser
)