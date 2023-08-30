#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "mcu/spi.h"
#include "mcu/gpio.h"
#include "mcu/uart.h"

class Pindar {
private:
public:
	// on board imu bus and GPIO_Normal
	Pindar();
	~Pindar();

	UART *uart1 = nullptr;
	UART *uart2 = nullptr;
	// I2C_Bus *i2c_bus = nullptr;
	SPI_Bus *spi2_bus = nullptr;
	SPI_Bus *spi3_bus = nullptr;

	GPIO_Interrupt *gpio_imu = nullptr;
	
	GPIO_Normal *gpio_1;
	GPIO_Normal *gpio_2;
	GPIO_Normal *gpio_3;
	GPIO_Normal *gpio_4;
	GPIO_Normal *gpio_5;
	GPIO_Normal *gpio_6;
	GPIO_Normal *gpio_7;
	GPIO_Normal *gpio_8;
	GPIO_Normal *gpio_9;
	GPIO_Normal *gpio_10;
	GPIO_Normal *gpio_11;
	GPIO_Normal *gpio_12;
};
