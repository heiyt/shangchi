//
// Created by heiyt on 25-3-25.
//

#include "wifi.h"

esp_mqtt_client_handle_t mqtt_client_handle;
SemaphoreHandle_t xSemaphore_wifi_to_mqtt;

void mqtt_event_callback(void* event_handler_arg,
                                    esp_event_base_t event_base,
                                    int32_t event_id,
                                    void* event_data)
{
    auto mqtt_data = static_cast<esp_mqtt_event_handle_t>(event_data);
    switch (event_id)
    {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI("mqtt", "MQTT_EVENT_CONNECTED");
            esp_mqtt_client_subscribe_single(mqtt_client_handle, MQTT_TOPIC1, 1);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI("mqtt", "MQTT_EVENT_DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI("mqtt", "MQTT_EVENT_SUBSCRIBED");
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI("mqtt", "MQTT_EVENT_PUBLISHED");
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI("mqtt", "topic->%.*s",
                mqtt_data->topic_len,
                mqtt_data->topic);
            ESP_LOGI("mqtt", "data->%.*s",
                mqtt_data->data_len,
                mqtt_data->data);
            break;
        default:
            break;
    }
}

void wifi_event_handler(void* event_handler_arg,
                                    esp_event_base_t event_base,
                                    int32_t event_id,
                                    void* event_data)
{
    if (event_base == WIFI_EVENT)
    {
        if (event_id == WIFI_EVENT_STA_START)
        {
            esp_wifi_connect();
        }
        if (event_id == WIFI_EVENT_STA_CONNECTED)
        {
            ESP_LOGI("wifi", "Connected to ap!");
        }
        if (event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
            esp_wifi_connect();
            ESP_LOGI("wifi", "Disconnected from ap! Retrying!");
        }
    }
    if (event_base == IP_EVENT)
    {
        if (event_id == IP_EVENT_STA_GOT_IP)
        {
            ESP_LOGI("wifi", "got ip!");
            xSemaphoreGive(xSemaphore_wifi_to_mqtt);
        }
    }
}

void tcp_init_softap(char *SSID,char *PASSWORD)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_register(WIFI_EVENT,ESP_EVENT_ANY_ID, wifi_event_handler,nullptr);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler,nullptr);
    wifi_config_t wifi_config;
    wifi_config.sta.threshold.authmode = WIFI_AUTH_OPEN;
    wifi_config.sta.pmf_cfg.capable = true;
    wifi_config.sta.pmf_cfg.required = false;
    memcpy(wifi_config.sta.ssid,SSID, strlen(SSID));
    memcpy(wifi_config.sta.password,PASSWORD, strlen(PASSWORD));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void mqtt_start()
{
    esp_mqtt_client_config_t mqtt_config;
    mqtt_config.broker.address.uri = MQTT_ADDRESS;
    mqtt_config.broker.address.port = MQTT_PORT;
    mqtt_config.credentials.client_id = MQTT_CLIENTID;
    mqtt_config.credentials.username = MQTT_USERNAME;
    mqtt_config.credentials.authentication.password = MQTT_PASSWORD;
    mqtt_client_handle = esp_mqtt_client_init(&mqtt_config);
    esp_mqtt_client_register_event(mqtt_client_handle, static_cast<esp_mqtt_event_id_t>(ESP_EVENT_ANY_ID), mqtt_event_callback,NULL);
    esp_mqtt_client_start(mqtt_client_handle);
}