#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "ESP8285.h"
#include "mqtt.h"


int main() {
    stdio_init_all();
    sleep_ms(2000);

    ESP8285Controller wifi;

    printf("=== ESP8285 WiFi ===\n");

    if (!wifi.sendCommand("AT")) {
        printf("No response from ESP8285. Check wiring.\n");
        while (true) tight_loop_contents();
    }

    wifi.sendCommand("AT+CWMODE=1");

    char join_cmd[128];
    snprintf(join_cmd, sizeof(join_cmd),
             "AT+CWJAP=\"%s\",\"%s\"", WIFI_SSID, WIFI_PASSWORD);
    if (!wifi.sendCommand(join_cmd, 20000)) {
        printf("WiFi connection failed.\n");
        while (true) tight_loop_contents();
    }

    wifi.sendCommand("AT+CIFSR");

    printf("Connected!\n");
    wifi.sendCommand("AT+GMR");

    printf("Start with mqtt!\n");

    MQTTController mqttConection = MQTTController("0","leaf1");

    printf("finish with mqtt user config!\n");

    mqttConection.connect("", 9001);

    while (true) {
        tight_loop_contents();
    }
}