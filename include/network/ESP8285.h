#pragma once

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

#define UART_ID      uart0
#define BAUD_RATE    115200
#define UART_TX_PIN  0
#define UART_RX_PIN  1

#define WIFI_SSID     "HUAWEI-4Ncg"
#define WIFI_PASSWORD "AcVvgU2z"

class ESP8285Controller {
public:
    ESP8285Controller();
    bool sendCommand(const char* cmd, uint32_t timeout_ms = 10000);

private:
    bool waitForResponse(uint32_t timeout_ms);
};