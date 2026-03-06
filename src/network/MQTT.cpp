#include "mqtt.h"

MQTTController::MQTTController(const char* user_id, const char* username, const char* password, int keepalive)
{
    config.user_id = user_id;
    config.username = username;
    config.password = password;

    config.lwt_topic = "leaf/status";
    config.lwt_msg = "disconnected";
    config.keepalive = keepalive;

    char commandUserConfig[250];
    snprintf(commandUserConfig, sizeof(commandUserConfig),
             "AT+MQTTUSERCFG=0,%d,\"%s\",\"%s\",\"%s\",0,0,\"\"", config.scheme, config.user_id,  config.username, config.password);
    
    if(!sendCommand(commandUserConfig)){
        printf(": Error with user configuration\n");
        return;
    } else {
        char commandMqttConfig[250];
        snprintf(commandMqttConfig, sizeof(commandMqttConfig),"AT+MQTTCONNCFG=0,%d,%d,\"%s\",\"%s\",%d,0", config.keepalive, config.disable_clean_session,  config.lwt_topic, config.lwt_msg, config.lwt_qos);
        if(!sendCommand(commandMqttConfig)){
            printf("Error with MQTT configuration\n");
            return;
        }
    };
}


MQTTController::~MQTTController(){

};

bool MQTTController::connect(const char* brokerIP, const int port, int reconnect, int timeout_ms){
    config.broker = brokerIP;
    config.port = port;
    config.reconnect = reconnect;
    config.timeout_ms = timeout_ms;

    char commandBrokerConfig[250];
    snprintf(commandBrokerConfig, sizeof(commandBrokerConfig),
        "AT+MQTTCONN=0,\"%s\",%d,%d,%d,", config.broker, config.port,  config.reconnect, config.timeout_ms);
    return sendCommand(commandBrokerConfig);
}
// bool MQTTController::subcriptTopic(const char* topic, int qos = 0);
// bool MQTTController::publish(const char* msg, const char* topic, int qos = 0);
// char* MQTTController::recievefrom(const char* topic, int qos = 0);
// bool MQTTController::disconnect();