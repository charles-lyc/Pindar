

#pragma once

#include <stdint.h>

#include "driver/gpio.h"

class GPIO
{
private:

public:
    GPIO(gpio_num_t gpio_num, gpio_isr_t isr, void *arg)
    {
    }
    ~GPIO()
    {
    }
};

class GPIO_PWM
{
private:

public:
    GPIO(gpio_num_t gpio_num, gpio_isr_t isr, void *arg)
    {
    }
    ~GPIO()
    {
    }
};

class GPIO_Interrupt
{
private:
    gpio_num_t pin;
    //     gpio_isr_t isr;
    // void *arg;
public:
    GPIO_Interrupt(gpio_num_t pin)
    {
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << pin),
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_POSEDGE,
        };
        gpio_config(&io_conf);
        gpio_set_intr_type(pin, GPIO_INTR_POSEDGE);
        gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
    }

    ~GPIO_Interrupt()
    {
        gpio_isr_handler_remove(pin);
    }

    /**
     * @brief 注册回调函数（与实际驱动无关，所以没放在构造函数中）
     * @param isr
     * @param arg
     */
    void set_callback(gpio_isr_t isr, void *arg = nullptr)
    {
        gpio_isr_handler_add(pin, isr, arg);
    }
};


