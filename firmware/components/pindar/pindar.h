#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "spi.h"
#include "gpio_intr.h"

class Pindar {
private:
public:
	// on board imu bus and gpio
	Pindar();
	~Pindar();

	// SerialPort *serial1= nullptr;
	// SerialPort *serial2= nullptr;

	SPI_Interface *spi2_bus = nullptr;
	SPI_Interface *spi3_bus = nullptr;
	// I2C_Interface *i2c_bus = nullptr;
	GPIO_Interrupt *gpio_imu = nullptr;

	// GPIO_Interface *gpio_1;
	// GPIO_Interface *gpio_2;
	// GPIO_Interface *gpio_3;
	// GPIO_Interface *gpio_4;
	// GPIO_Interface *gpio_5;
	// GPIO_Interface *gpio_6;
	// GPIO_Interface *gpio_7;
	// GPIO_Interface *gpio_8;
	// GPIO_Interface *gpio_9;
	// GPIO_Interface *gpio_10;
	// GPIO_Interface *gpio_11;
	// GPIO_Interface *gpio_12;
};
