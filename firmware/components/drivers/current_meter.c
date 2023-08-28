#include "../pindar_config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

int current_meter_init()
{
    adc_dma_on;

    return 0;
}

float current_meter_read()
{
    return adc * FACTOR / 1000;
}

float voltage_meter_read()
{
    return adc * FACTOR / 1000;
}

