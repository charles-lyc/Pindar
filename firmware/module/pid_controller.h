#pragma once

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_spi_flash.h"

class PID_Controller:public Controller_Interface, public lpf1_filter
{
private:
    float 
public:
     PID_Controller() {}
     ~PID_Controller() {}

     int deinit() override 
     { return -1; }
     float calc_output(float error) override
     { return 0.0; }
};