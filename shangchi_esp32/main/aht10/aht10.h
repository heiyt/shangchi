//
// Created by heiyt on 25-3-22.
//

#ifndef AHT10_H
#define AHT10_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soft_iic.h"

#define AHT10_ADDRESS 0x38

class shangchi_aht10 {
private:
    static void aht10_write_byte(uint8_t *data, uint8_t len);
public:
    shangchi_aht10();
    ~shangchi_aht10();
    static void aht10_read_data(float* humi, float* temp);
};

#endif //AHT10_H
