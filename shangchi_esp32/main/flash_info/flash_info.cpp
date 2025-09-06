
#include "flash_info.h"

uint8_t shangchi_flash_info::sensors_enable = 0;
shangchi_oled* shangchi_flash_info::oled_instance = nullptr;
shangchi_aht10* shangchi_flash_info::aht10_instance = nullptr;

shangchi_flash_info::shangchi_flash_info() {
    nvs_flash_init();
    nvs_handle_t nvs_handle;
    nvs_open("storage", NVS_READWRITE, &nvs_handle);
    esp_err_t err = nvs_get_u8(nvs_handle, "sensors_enable", &sensors_enable);
    if (err != ESP_OK) {
        sensors_enable = 0;
        nvs_set_u8(nvs_handle, "sensors_enable", sensors_enable);
        nvs_commit(nvs_handle);
    }
    nvs_close(nvs_handle);

    if (sensors_enable == 1) {
        // 初始化OLED
        oled_instance = new shangchi_oled();
        ESP_LOGI("FlashInfo", "OLED initialized based on sensors_enable");
    } else if (sensors_enable == 2) {
        // 初始化AHT10
        aht10_instance = new shangchi_aht10();
        ESP_LOGI("FlashInfo", "AHT10 initialized based on sensors_enable");
    } else {
        ESP_LOGI("FlashInfo", "No sensors initialized based on sensors_enable");
    }
}
void shangchi_flash_info::flash_info_get(const char *key,uint8_t *value) {
    nvs_handle_t nvs_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &nvs_handle));
    nvs_get_u8(nvs_handle, key, value);
    nvs_close(nvs_handle);
}
void shangchi_flash_info::flash_info_update(const char *key, const uint8_t value) {
    nvs_handle_t nvs_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &nvs_handle));
    nvs_set_u8(nvs_handle, key, value);
    nvs_commit(nvs_handle);
    nvs_close(nvs_handle);
}