#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "irq.h"
#include "flash_info.h"
#include "axp2101.h"
#include "shangchi_debug.h"

extern "C" void app_main()
{
    // 初始化gpio中断
    shangchi_irq shangchi_irq_handler{};
    // 从flash加载设置项
    shangchi_flash_info shangchi_flash_info_handler{};
    // 初始化axp2101
    shangchi_axp2101 shangchi_axp2101_handler{};

    xTaskCreatePinnedToCore(debug_task, "debug_task", 8 * 1024, nullptr, 5, nullptr, 0);
}
