#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"

class PulseGen {
private:

public:
	PulseGen(gpio_num_t pin_1, gpio_num_t pin_2)
	{
        
	}
	~PulseGen();

	void set_freq(uint32_t freq)
	{

	}

};
