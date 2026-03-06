#pragma once

#include <stdio.h>
#include "ESP8285.h"


struct mqttConfig
{
    const char* user_id;
    const char* username;
    const char* password;
    int scheme = 1; //1: MQTT over TCP. 2: MQTT over TLS (no certificate verify).3: MQTT over TLS (verify server certificate). 4: MQTT over TLS (provide client certificate). 6: MQTT over WebSocket (based on TCP).

    int keepalive = 120;
    int disable_clean_session = 0;
    const char* lwt_topic;
    const char* lwt_msg;
    int lwt_qos = 2;

    const char* broker = "";
    int port = 0;
    int reconnect = 1;
    int timeout_ms = 120;
    int qos = 0;
};


class MQTTController : public ESP8285Controller {
public:
    MQTTController( const char* user_id, 
                    const char* username = "leaf", 
                    const char* password = "", 
                    int keepalive = 120);

    ~MQTTController();

    bool connect(const char* brokerIP, int port, int reconnect = 1, int timeout_ms = 120);
    bool subcriptTopic(const char* topic, int qos = 0);
    bool publish(const char* msg, const char* topic, int qos = 0);
    char* recievefrom(const char* topic, int qos = 0);
    bool disconnect();

private:
    mqttConfig config;
};
