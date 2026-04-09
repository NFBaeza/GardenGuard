#pragma once

#include "lwip/apps/mqtt.h"

// Connect to the broker defined in main.h (BROKER_IP / BROKER_PORT).
// Blocks (with cyw43_arch_poll) until accepted or 10 s timeout.
bool mqtt_connect(mqtt_client_t *client, const char *client_id);

// Publish a moisture reading. topic defaults to "sensors/moisture_level/".
// Blocks (with cyw43_arch_poll) until ack or 5 s timeout.
bool mqtt_publish_moisture(mqtt_client_t *client,
                           const char *device_id,
                           int         moisture_pct,
                           const char *topic = "sensors/moisture_level/");