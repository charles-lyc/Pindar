#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include "spi.h"
#include "gpio_intr.h"

class Pindar
{
public:
    // on board imu bus and gpio
    Pindar());
    ~Pindar();

    SPI_Interface *spi2_handle = nullptr;
    SPI_Interface *spi3_handle = nullptr;
    GPIOInterrupt *gpio_intr_imu = nullptr;

private:
};
