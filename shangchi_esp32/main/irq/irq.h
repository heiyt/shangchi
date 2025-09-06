
#ifndef SHANGCHI_ESP32_IRQ_H
#define SHANGCHI_ESP32_IRQ_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include "esp_log.h"

#include "axp2101.h"

class shangchi_irq {
    static QueueHandle_t gpio_evt_queue;
public:
    shangchi_irq();
    ~shangchi_irq();
    static void irq_handler_task(void *arg);
    static void irq_handler(void *pin_num) {
        xQueueSendFromISR(gpio_evt_queue, &pin_num, nullptr);
    }
};


#endif //SHANGCHI_ESP32_IRQ_H