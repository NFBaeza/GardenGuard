#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "ESP8285.h"
#include "mqtt.h"
#include "main.h"
#include "sleep_manager.h"


#define airLevelSensor      2.77
#define waterLevelSensor    1.02

const float conversion_factor = 3.3f / (1 << 12);

int main() {
    stdio_init_all();
    sleep_ms(2000);

    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    printf("=== ESP8285 WiFi ===\n");
    auto& wifi = ESP8285Controller::instance();
    wifi.connectWiFi(WIFI_SSID, WIFI_PASSWORD);
    wifi.getIP();

    while (true) {
        MQTTController mqttConection = MQTTController("0", "leaf1");
        while (!mqttConection.connect(BROKER_IP, BROKER_PORT)){sleep_ms(5000);} 

        float result = adc_read();
        float voltageValue = result * conversion_factor;
        int percentageMoisture = ((airLevelSensor - voltageValue) / (airLevelSensor - waterLevelSensor)) * 100;
        printf("moisture Level %%: %d\n", percentageMoisture);

        char payload[128];
        snprintf(payload, sizeof(payload),
            "{\"device_id\":%s,\"moisture\":%.1f,\"unit\":\"%%\"}",
            mqttConection.,percentageMoisture
        );

        while(!mqttConection.publish2Topic(std::to_string(percentageMoisture).c_str(), "sensors/moisture_level/", 0)){
            sleep_ms(5000);
            printf("somthing fails\n");
        }
        printf("setting a sleeping mode\n");
        wifi.sendCommand("AT+SLEEPWKCFG=0,300000");  // ESP8285 dormant 5 min
        dormant_sleep();                             // Pico dormant 5 min

        printf("waking up\n");
        while (!wifi.connectWiFi(WIFI_SSID, WIFI_PASSWORD)){sleep_ms(5000);} 
    }
}
