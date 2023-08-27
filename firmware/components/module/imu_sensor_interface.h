
#pragma once

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_spi_flash.h"

class IMU_Interface
{
public:
    virtual ~IMU_Interface() {} // 确保能调用派生类的析构，又不至于在没有派生析构时没有析构函数导致奔溃

    virtual int probe() { return -1; }
    virtual int initialize() { return -1; }
    virtual int read_raw_data(int32_t *gyro, int32_t *accel, int16_t *temperature) { return -1; }
    virtual int set_data_rate(int data_rate) { return -1; }
    virtual int set_gyro_full_scale(int gyro_full_scale) { return -1; }
    virtual int set_accel_full_scale(int accel_full_scale) { return -1; }
};
