
#include "irq.h"

QueueHandle_t shangchi_irq::gpio_evt_queue = nullptr;

shangchi_irq::shangchi_irq() {
    gpio_evt_queue = xQueueCreate(5, sizeof(gpio_num_t));
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL<<PMU_INPUT_PIN);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(PMU_INPUT_PIN, irq_handler, reinterpret_cast<void *>(PMU_INPUT_PIN));
    ESP_LOGI("irq:","init");
    // 新建中断任务函数
    xTaskCreatePinnedToCore(irq_handler_task, "Axp2101_irq", 2 * 1024, nullptr, 10, nullptr, 0);
}

shangchi_irq::~shangchi_irq() {
    if (gpio_evt_queue != nullptr) {
        vQueueDelete(gpio_evt_queue);
    }
    gpio_isr_handler_remove(PMU_INPUT_PIN);
    ESP_LOGI("irq:","deinit");
}

void shangchi_irq::irq_handler_task(void* arg) {
    uint32_t io_num;
    while (true) {
        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            if (io_num == PMU_INPUT_PIN) {
                shangchi_axp2101::pmu_isr_handler();
            }
        }
    }
}
