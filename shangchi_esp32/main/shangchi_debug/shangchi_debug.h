
#ifndef SHANGCHI_ESP32_TASKS_H
#define SHANGCHI_ESP32_TASKS_H

// 声明命令注册函数
void register_axp2101_commands();
void register_aht10_commands();
void register_oled_commands();
void register_system_commands();
void debug_task(void* arg);

#endif //SHANGCHI_ESP32_TASKS_H