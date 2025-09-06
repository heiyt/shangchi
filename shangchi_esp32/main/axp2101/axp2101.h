
#ifndef SHANGCHI_ESP32_AXP2101_H
#define SHANGCHI_ESP32_AXP2101_H

#define XPOWERS_CHIP_AXP2101
#include "XPowersLib.h"
#define PMU_INPUT_PIN (gpio_num_t)CONFIG_PMU_INTERRUPT_PIN    /*!< axp power chip interrupt Pin*/

class shangchi_axp2101 {
    static int pmu_register_read(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t len);
    static int pmu_register_write_byte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t len);
    static esp_err_t i2c_init_axp2101();
public:
    shangchi_axp2101();
    ~shangchi_axp2101();

    static XPowersPMU PMU;
    static void pmu_isr_handler();
};

#endif //SHANGCHI_ESP32_AXP2101_H