#ifndef __OLED_H
#define __OLED_H

#include "esp_err.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

#define I2C_ADDRESS 0x3C

class shangchi_oled{
private:
    static void oled_write_data(uint8_t data);
    static void oled_write_cmd(uint8_t data);
public:
    shangchi_oled();
    ~shangchi_oled();
    static void oled_clear();
    static void oled_set_pos(uint8_t x, uint8_t y);
    static void oled_show_char(uint8_t x, uint8_t y, char chr);
    static void oled_show_string(uint8_t x, uint8_t y, char *str);
};

#endif

