
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Important for binary compatibility

cmake_policy(SET CMP0079 NEW)
add_subdirectory(UART)
add_subdirectory(JsonParser)
add_subdirectory(MQTT)

# PUBLIC means "anyone linking to 'common' also gets these paths"
target_link_libraries(UART PUBLIC JsonParser)
