# Find JsonCpp
find_package(jsoncpp REQUIRED)

add_library(common STATIC
    src/logger.cpp
    src/JsonParser.cpp
)

# PUBLIC means "anyone linking to 'common' also gets these paths"
target_include_directories(common PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "/usr/local/include"
)

target_link_libraries(common 
    PUBLIC 
    /usr/local/lib/libserial.a   
    jsoncpp_lib                  
)