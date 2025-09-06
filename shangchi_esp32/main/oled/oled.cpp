#include "oled.h"
#include "oledfont.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "soft_iic.h"

// 向OLED发送命令
void shangchi_oled::oled_write_cmd(uint8_t cmd) {
    i2c_start();
    i2c_send_byte(I2C_ADDRESS << 1); // 写模式
    i2c_send_byte(0x00); // 控制字节，命令
    i2c_send_byte(cmd);
    i2c_stop();
}
// 向OLED发送数据
void shangchi_oled::oled_write_data(uint8_t data) {
    i2c_start();
    i2c_send_byte(I2C_ADDRESS << 1); // 写模式
    i2c_send_byte(0x40); // 控制字节，数据
    i2c_send_byte(data);
    i2c_stop();
}
// 清屏
void shangchi_oled::oled_clear() {
    for (uint8_t page = 0; page < 8; page++) {
        oled_write_cmd(0xB0 + page); // 设置页地址
        oled_write_cmd(0x00);       // 设置列地址低4位
        oled_write_cmd(0x10);       // 设置列地址高4位
        for (uint8_t col = 0; col < 128; col++) {
            oled_write_data(0x00);  // 写入0清空
        }
    }
}
// 设置光标位置
void shangchi_oled::oled_set_pos(uint8_t x, uint8_t y) {
    oled_write_cmd(0xB0 + y);                            // 设置页地址
    oled_write_cmd((x & 0xF0) >> 4 | 0x10);           // 设置列地址高4位
    oled_write_cmd((x & 0x0F) | 0x00);                  // 设置列地址低4位
}
// 显示一个字符 (6x8)
void shangchi_oled::oled_show_char(uint8_t x, uint8_t y, char chr) {
    uint8_t c = chr - ' ';
    oled_set_pos(x, y);
    for (uint8_t i = 0; i < 6; i++) {
        oled_write_data(asc2_0806[c][i]);
    }
}
// 显示字符串
void shangchi_oled::oled_show_string(uint8_t x, uint8_t y, char *str) {
    uint8_t j = 0;
    while (str[j] != '\0') {
        oled_show_char(x, y, str[j]);
        x += 6;
        if (x > 122) {
            x = 0;
            y++;
        }
        j++;
    }
}

shangchi_oled::shangchi_oled() {
    i2c_init();
    oled_write_cmd(SSD1306_DISPLAYOFF); // 0xAE
    oled_write_cmd(SSD1306_SETDISPLAYCLOCKDIV); // 0xD5
    oled_write_cmd(0x80); // 建议比率 0x80
    oled_write_cmd(SSD1306_SETMULTIPLEX); // 0xA8
    oled_write_cmd(0x3F); // 0x3F 1/64 duty
    oled_write_cmd(SSD1306_SETDISPLAYOFFSET); // 0xD3
    oled_write_cmd(0x0); // no offset
    oled_write_cmd(SSD1306_SETSTARTLINE | 0x0); // line #0
    oled_write_cmd(SSD1306_CHARGEPUMP); // 0x8D
    oled_write_cmd(0x14); // 0x14 enable, 0x10 disable
    oled_write_cmd(SSD1306_MEMORYMODE); // 0x20
    oled_write_cmd(0x00); // 0x00 horizontal addressing
    oled_write_cmd(SSD1306_SEGREMAP | 0x1); // 0xA1
    oled_write_cmd(SSD1306_COMSCANDEC); // 0xC8
    oled_write_cmd(SSD1306_SETCOMPINS); // 0xDA
    oled_write_cmd(0x12); // 0x12
    oled_write_cmd(SSD1306_SETCONTRAST); // 0x81
    oled_write_cmd(0xCF); // 0xCF
    oled_write_cmd(SSD1306_SETPRECHARGE); // 0xD9
    oled_write_cmd(0xF1); // 0xF1
    oled_write_cmd(SSD1306_SETVCOMDETECT); // 0xDB
    oled_write_cmd(0x40); // 0x40
    oled_write_cmd(SSD1306_DISPLAYALLON_RESUME); // 0xA4
    oled_write_cmd(SSD1306_NORMALDISPLAY); // 0xA6
    oled_write_cmd(SSD1306_DISPLAYON); // 0xAF
    oled_clear();
}

shangchi_oled::~shangchi_oled() = default;
