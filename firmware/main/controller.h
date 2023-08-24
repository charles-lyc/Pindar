#pragma once

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_spi_flash.h"

class Controller_Interface
{
public:
    virtual ~Controller_Interface() {} // 确保能调用派生类的析构，又不至于在没有派生析构时没有析构函数导致奔溃

    virtual int deinit() { return -1; }
    virtual float calc_output(float error) { return 0.0; }
    virtual double calc_output(double error) { return 0.0; }
};