
#ifndef SHANGCHI_ESP32_NVS_FLASH_H
#define SHANGCHI_ESP32_NVS_FLASH_H

#include "esp_log.h"
#include "esp_err.h"

#include "nvs_flash.h"

#include "oled.h"
#include "aht10.h"

class shangchi_flash_info {
public:
    static uint8_t sensors_enable;
    static shangchi_oled* oled_instance;
    static shangchi_aht10* aht10_instance;

    shangchi_flash_info();

    static void flash_info_get(const char *key, uint8_t *value);
    static void flash_info_update(const char *key, uint8_t value);
};

#endif //SHANGCHI_ESP32_NVS_FLASH_H