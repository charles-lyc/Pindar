

#pragma once

#include <stdint.h>

#include "driver/gpio.h"

class GPIO_Normal {
private:
	gpio_num_t gpio_num = GPIO_NUM_NC;

public:
	enum GPIO_TYPE {
		DISABLE = 0,
		ANOLOG_INPUT,
		ANOLOG_OUTPUT,
		DIGTAL_INPUT,
		DIGTAL_OUTPUT,
		DIGTAL_INnOUTPUT,
		DIGTAL_OD,
	};

	GPIO_Normal(gpio_num_t io, enum GPIO_TYPE type): gpio_num(io)
	{
		gpio_config_t io_conf = {
			.pin_bit_mask = BIT64(io),
			.mode = GPIO_MODE_DISABLE,
			.pull_up_en = GPIO_PULLUP_DISABLE,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.intr_type = GPIO_INTR_DISABLE,
		};

		switch (type) {
			case DISABLE:
				io_conf.mode = GPIO_MODE_DISABLE;
				break;
			case ANOLOG_INPUT:
				io_conf.mode = GPIO_MODE_INPUT;
				break;
			case ANOLOG_OUTPUT:
				io_conf.mode = GPIO_MODE_OUTPUT;
				break;
			case DIGTAL_INPUT:
				io_conf.mode = GPIO_MODE_INPUT;
				break;
			case DIGTAL_OUTPUT:
				io_conf.mode = GPIO_MODE_OUTPUT;
				break;
			case DIGTAL_INnOUTPUT:
				io_conf.mode = GPIO_MODE_INPUT_OUTPUT;
				break;
			case DIGTAL_OD:
				io_conf.mode = GPIO_MODE_INPUT_OUTPUT_OD;
				break;
			default:
				io_conf.mode = GPIO_MODE_DISABLE;
		}

		gpio_config(&io_conf);
	}
	~GPIO_Normal()
	{
	}

	int set(uint32_t level)
	{
		return  gpio_set_level(gpio_num, level);
	}

	int get()
	{
		return gpio_get_level(gpio_num);
	}

	int toggle()
	{
		int level = gpio_get_level(gpio_num);
		return  gpio_set_level(gpio_num, level ? 0 : 1);
	}
};

class GPIO_PWM {
private:

public:
	GPIO_PWM(gpio_num_t gpio_num)
	{
	}
	~GPIO_PWM()
	{
	}
};

class GPIO_Interrupt {
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


