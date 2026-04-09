#include <stdio.h>
#include <cstring>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "hardware/watchdog.h"

#include "main.h"
#include "sleep_manager.h"
#include "mqtt.h"

#define airLevelSensor    2.77f
#define waterLevelSensor  1.02f

static const float conversion_factor = 3.3f / (1 << 12);

// ── WiFi ──────────────────────────────────────────────────────────────────────
static bool wifi_connect() {
    return cyw43_arch_wifi_connect_timeout_ms(
        WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) == 0;
}


// ── Main ──────────────────────────────────────────────────────────────────────

int main() {
    stdio_init_all();
    sleep_ms(2000);

    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    if (cyw43_arch_init()) {
        printf("CYW43 init failed\n");
        return 1;
    }
    cyw43_arch_enable_sta_mode();

    printf("=== GardenGuard (Pico 2 W) ===\n");

    printf("Connecting to WiFi...\n");
    while (!wifi_connect()) {
        printf("WiFi failed, retrying...\n");
        sleep_ms(5000);
    }
    printf("WiFi connected\n");

    while (true) {
        mqtt_client_t *mqtt_client = mqtt_client_new();
        printf("Connecting to MQTT broker...\n");
        while (!mqtt_connect(mqtt_client, "leaf1")) {
            sleep_ms(5000);
        }
        printf("MQTT connected\n");

        float voltage     = adc_read() * conversion_factor;
        int moisture_pct  = (int)(((airLevelSensor - voltage) /
                                   (airLevelSensor - waterLevelSensor)) * 100.0f);
        printf("Moisture: %d%%\n", moisture_pct);

        while (!mqtt_publish_moisture(mqtt_client, "leaf1", moisture_pct)) {
            printf("Publish failed, retrying...\n");
            sleep_ms(5000);
        }
        printf("Published. Entering sleep...\n");

        mqtt_disconnect(mqtt_client);
        mqtt_client_free(mqtt_client);

        cyw43_arch_deinit();

        printf("Sleeping...\n");
        deep_sleep(SLEEP_DURATION_MS_DEFAULT);

        printf("Woke up, arming watchdog and re-initialising CYW43...\n");
        watchdog_enable(15000, true);   // 15 s, pause on debugger

        if (cyw43_arch_init()) {
            printf("CYW43 re-init failed — letting watchdog reboot\n");
            while (true) { tight_loop_contents(); }   // watchdog bites
        }
        watchdog_update();
        cyw43_arch_enable_sta_mode();
        watchdog_update();

        printf("Reconnecting WiFi...\n");
        while (!wifi_connect()) {
            printf("WiFi reconnect failed, retrying...\n");
            sleep_ms(2000);
        }
        printf("WiFi reconnected\n");

        watchdog_enable(0x7fffff, true);   // ~8388 s ≈ effectively off
    }
}