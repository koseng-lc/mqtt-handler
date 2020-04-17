cmake_minimum_required(VERSION 2.8.3)
project(mqtt_handler)

find_package(PahoMqttCpp REQUIRED)

add_library(mqtt_handler mqtt_handler.hpp)
set_target_properties(mqtt_handler PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(mqtt_handler paho-mqtt3as paho-mqttpp3)
