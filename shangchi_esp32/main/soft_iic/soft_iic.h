//
// Created by heiyt on 8/13/25.
//

#ifndef SHANGCHI_ESP32_SOFT_IIC_H
#define SHANGCHI_ESP32_SOFT_IIC_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define I2C_SDA_GPIO (gpio_num_t)12
#define I2C_SCL_GPIO (gpio_num_t)13

void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_send_byte(uint8_t byte);
uint8_t i2c_recv_byte(bool send_nack);

#endif //SHANGCHI_ESP32_SOFT_IIC_H