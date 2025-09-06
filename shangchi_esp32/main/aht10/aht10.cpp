
#include "aht10.h"

shangchi_aht10::shangchi_aht10() {
    i2c_init();
}
shangchi_aht10::~shangchi_aht10() = default;

void shangchi_aht10::aht10_write_byte(uint8_t *data, const uint8_t len)
{
    for (int i = 0; i < len; i++) {
        i2c_send_byte(data[i]);
    }
}
void shangchi_aht10::aht10_read_data(float* humi, float* temp)
{
    uint8_t command[] = {0xac, 0x33, 0x00};
    uint8_t data[6] = {0};
    uint32_t t = 0;
    // 发送起始信号
    i2c_start();
    i2c_send_byte(AHT10_ADDRESS << 1);
    aht10_write_byte(command, sizeof(command));
    i2c_start();
    i2c_send_byte((AHT10_ADDRESS << 1) | 0x01);
    for (int i = 0; i < sizeof(data); i++) {
        data[i] = i2c_recv_byte(i == sizeof(data) - 1);
    }
    i2c_stop();
    t = data[1] << 12 | data[2] << 4 | data[3] >> 4;
    *humi = static_cast<float>(t) / (1UL << 20) * 100.0f;
    t = (data[3] & 0x0f) << 16 | data[4] << 8 | data[5];
    *temp = static_cast<float>(t) / (1UL << 20) * 200.0f - 50.0f;
}