//
// Created by heiyt on 8/13/25.
//

#include "soft_iic.h"

void delay_us(uint32_t us) {
    esp_rom_delay_us(us);
}
// 延迟函数
void delay_ms(uint32_t ms) {
    vTaskDelay(ms / portTICK_PERIOD_MS);

}
// 软件I2C初始化
void i2c_init() {
    gpio_set_direction(I2C_SDA_GPIO, GPIO_MODE_INPUT_OUTPUT_OD);
    gpio_set_direction(I2C_SCL_GPIO, GPIO_MODE_INPUT_OUTPUT_OD);
    gpio_set_level(I2C_SDA_GPIO, 1);
    gpio_set_level(I2C_SCL_GPIO, 1);
}
// I2C起始信号
void i2c_start() {
    gpio_set_level(I2C_SDA_GPIO, 1);
    gpio_set_level(I2C_SCL_GPIO, 1);
    delay_ms(1);
    gpio_set_level(I2C_SDA_GPIO, 0);
    delay_ms(1);
    gpio_set_level(I2C_SCL_GPIO, 0);
    delay_ms(1);
}
// I2C停止信号
void i2c_stop() {
    gpio_set_level(I2C_SCL_GPIO, 0);
    gpio_set_level(I2C_SDA_GPIO, 0);
    delay_ms(1);
    gpio_set_level(I2C_SCL_GPIO, 1);
    delay_ms(1);
    gpio_set_level(I2C_SDA_GPIO, 1);
    delay_ms(1);
}
// I2C发送一个字节
void i2c_send_byte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        gpio_set_level(I2C_SCL_GPIO, 0);
        delay_ms(1);
        if (byte & 0x80) {
            gpio_set_level(I2C_SDA_GPIO, 1);
        } else {
            gpio_set_level(I2C_SDA_GPIO, 0);
        }
        byte <<= 1;
        delay_ms(1);
        gpio_set_level(I2C_SCL_GPIO, 1);
        delay_ms(1);
    }
    // 等待ACK
    gpio_set_level(I2C_SCL_GPIO, 0);
    gpio_set_level(I2C_SDA_GPIO, 1);
    delay_ms(1);
    gpio_set_level(I2C_SCL_GPIO, 1);
    delay_ms(1);
    gpio_set_level(I2C_SCL_GPIO, 0);
}
// I2C 接收一个字节
uint8_t i2c_recv_byte(bool send_nack) {
    uint8_t byte = 0;
    gpio_set_direction(I2C_SDA_GPIO, GPIO_MODE_INPUT);
    gpio_set_level(I2C_SDA_GPIO, 1);
    for (int i = 0; i < 8; i++) {
        gpio_set_level(I2C_SCL_GPIO, 0);
        delay_us(5);
        gpio_set_level(I2C_SCL_GPIO, 1);
        delay_us(5);
        byte = (byte << 1) | (gpio_get_level(I2C_SDA_GPIO) & 0x01);
        delay_us(5);
    }
    gpio_set_level(I2C_SCL_GPIO, 0);
    gpio_set_direction(I2C_SDA_GPIO, GPIO_MODE_OUTPUT_OD);
    gpio_set_level(I2C_SDA_GPIO, send_nack ? 1 : 0);
    delay_us(5);
    gpio_set_level(I2C_SCL_GPIO, 1);
    delay_us(5);
    gpio_set_level(I2C_SCL_GPIO, 0);
    gpio_set_level(I2C_SDA_GPIO, 1);
    delay_us(5);
    return byte;
}