#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include "pico/stdlib.h"
#include "ESP8285.h"
#include "mqtt.h"
#include "main.h"


int main() {
    stdio_init_all();
    sleep_ms(2000);
    
    printf("=== ESP8285 WiFi ===\n");

    auto& wifi = ESP8285Controller::instance();

    wifi.connectWiFi(WIFI_SSID, WIFI_PASSWORD);
    wifi.getIP();
 
    printf("=== ESP8285 MQTT ===\n");

    MQTTController mqttConection = MQTTController("0","leaf1");

    mqttConection.connect(BROKER_IP, BROKER_PORT);
    mqttConection.subcriptTopic("sensors/", 0);
  

    while (true) {
        tight_loop_contents();
    }
}