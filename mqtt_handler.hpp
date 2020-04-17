/**
*   @author : koseng (Lintang)
*   @brief : MQTT Handler
*/
#pragma once

#include <mqtt/client.h>

#define MICRON_MQTT_EXCEPTIONAL_HANDLER(x) try{x}catch(const mqtt::exception& e){std::cerr << e.what() << std::endl;}

namespace micron{

class MQTTHandler{
public:
    MQTTHandler(const std::string& _username,
                const std::string& _key,
                const std::string& _addr = "io.adafruit.com",
                const std::string& _client_id = "")
        : cli_(_addr, _client_id){
        mqtt::connect_options opts(_username, _key);
        opts.set_keep_alive_interval(20);
        opts.set_clean_session(true);
        MICRON_MQTT_EXCEPTIONAL_HANDLER(
            cli_.connect(opts);
        )
    }
    ~MQTTHandler(){
        cli_.disconnect();
    }

    auto send(const std::string& _topic, const std::string& _data) -> void{
        auto msg( mqtt::make_message(_topic, _data) );
        msg->set_qos(qos_);
        MICRON_MQTT_EXCEPTIONAL_HANDLER(
            cli_.publish(msg);
        )
    }

    auto isConnected() -> decltype(std::declval<mqtt::client>().is_connected()) {
        return cli_.is_connected();
    }

    auto disconnect() -> decltype(std::declval<mqtt::client>().disconnect()){
        return cli_.disconnect();
    }
private:
    const int qos_{1};
    mqtt::client cli_;

};

}
