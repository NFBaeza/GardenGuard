#include "mqtt.h"

#include <cstring>
#include <cstdio>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/ip_addr.h"

#include "main.h"

// ── Async state (one copy, lives here in the .cpp) ───────────────────────────

static volatile bool s_mqtt_connected = false;
static volatile bool s_pub_done       = false;
static volatile bool s_pub_ok         = false;

// ── Callbacks ─────────────────────────────────────────────────────────────────

static void on_mqtt_connection(mqtt_client_t *, void *, mqtt_connection_status_t status) {
    s_mqtt_connected = (status == MQTT_CONNECT_ACCEPTED);
}

static void on_mqtt_publish(void *, err_t result) {
    s_pub_ok   = (result == ERR_OK);
    s_pub_done = true;
}

// ── Public API ────────────────────────────────────────────────────────────────

bool mqtt_connect(mqtt_client_t *client, const char *client_id) {
    ip_addr_t broker_addr;
    if (!ipaddr_aton(BROKER_IP, &broker_addr)) {
        printf("Invalid broker IP\n");
        return false;
    }

    struct mqtt_connect_client_info_t ci = {};
    ci.client_id = client_id;

    s_mqtt_connected = false;

    // All lwIP API calls must be guarded by begin/end in cyw43_arch poll mode
    cyw43_arch_lwip_begin();
    err_t err = mqtt_client_connect(
        client, &broker_addr, BROKER_PORT,
        on_mqtt_connection, NULL, &ci);
    cyw43_arch_lwip_end();

    if (err != ERR_OK) {
        printf("mqtt_client_connect error: %d\n", (int)err);
        return false;
    }

    uint32_t deadline = to_ms_since_boot(get_absolute_time()) + 10000;
    while (!s_mqtt_connected) {
        cyw43_arch_poll();
        if (to_ms_since_boot(get_absolute_time()) > deadline) {
            printf("MQTT connect timeout\n");
            return false;
        }
        sleep_ms(1);
    }
    return true;
}

bool mqtt_publish_moisture(mqtt_client_t *client,
                           const char *device_id,
                           int         moisture_pct,
                           const char *topic) {
    char payload[128];
    snprintf(payload, sizeof(payload),
        "{\"device_id\":\"%s\",\"moisture\":%d,\"unit\":\"%%\"}",
        device_id, moisture_pct);

    s_pub_done = false;
    s_pub_ok   = false;

    cyw43_arch_lwip_begin();
    err_t err = mqtt_publish(
        client, topic,
        payload, strlen(payload),
        /*qos=*/0, /*retain=*/0,
        on_mqtt_publish, NULL);
    cyw43_arch_lwip_end();

    if (err != ERR_OK) {
        printf("mqtt_publish error: %d\n", (int)err);
        return false;
    }

    uint32_t deadline = to_ms_since_boot(get_absolute_time()) + 5000;
    while (!s_pub_done) {
        cyw43_arch_poll();
        if (to_ms_since_boot(get_absolute_time()) > deadline) {
            printf("Publish timeout\n");
            return false;
        }
        sleep_ms(1);
    }
    return s_pub_ok;
}
