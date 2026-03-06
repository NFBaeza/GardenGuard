#include "ESP8285.h"


#define UART_ID      uart0
#define BAUD_RATE    115200
#define UART_TX_PIN  0
#define UART_RX_PIN  1

#define WIFI_SSID     "HUAWEI-4Ncg"
#define WIFI_PASSWORD "AcVvgU2z"

ESP8285Controller::ESP8285Controller() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

bool ESP8285Controller::sendCommand(const char* cmd, uint32_t timeout_ms) {
    // Flush any stale data
    while (uart_is_readable(UART_ID)) uart_getc(UART_ID);

    printf("> %s\n", cmd);
    uart_puts(UART_ID, cmd);
    uart_puts(UART_ID, "\r\n");

    return waitForResponse(timeout_ms);
}

bool ESP8285Controller::waitForResponse(uint32_t timeout_ms) {
    char buf[256];
    int  pos = 0;
    absolute_time_t deadline = make_timeout_time_ms(timeout_ms);

    while (!time_reached(deadline)) {
        if (!uart_is_readable_within_us(UART_ID, 10000)) continue;

        char c = uart_getc(UART_ID);
        putchar(c);

        if (pos < (int)sizeof(buf) - 1) buf[pos++] = c;
        buf[pos] = '\0';

        if (strstr(buf, "OK\r\n") || strstr(buf, "OK\n"))      return true;
        if (strstr(buf, "ERROR") || strstr(buf, "FAIL"))        return false;
    }
    printf("[timeout]\n");
    return false;
}