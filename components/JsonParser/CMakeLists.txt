set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Important for binary compatibility

find_package(jsoncpp REQUIRED)
add_library(JsonParser STATIC
    JsonParser.cpp
)

target_include_directories(JsonParser
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(JsonParser 
    PUBLIC 
    jsoncpp
)
