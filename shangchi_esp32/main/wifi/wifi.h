//
// Created by heiyt on 8/11/25.
//

#ifndef SHANGCHI_ESP32_WIFI_H
#define SHANGCHI_ESP32_WIFI_H

#include <esp_event.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <esp_wifi.h>
#include <esp_wifi_default.h>
#include <nvs_flash.h>
#include "mqtt_client.h"

#define MQTT_ADDRESS "mqtt://192.168.1.103"
#define MQTT_PORT 1883
#define MQTT_CLIENTID "LCKFB_ESP32"
#define MQTT_USERNAME "esp32s3"
#define MQTT_PASSWORD "12345678"
#define MQTT_TOPIC1 "topic/esp32_0326"
#define MQTT_TOPIC2 "topic/python_0326"

extern esp_mqtt_client_handle_t mqtt_client_handle;
extern SemaphoreHandle_t xSemaphore_wifi_to_mqtt;

void tcp_init_softap();
void mqtt_start();

#endif //SHANGCHI_ESP32_WIFI_H