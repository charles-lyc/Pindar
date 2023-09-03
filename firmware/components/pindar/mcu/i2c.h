#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "mcu/bus.h"
#include "driver/i2c.h"

class I2C_Bus : public Bus_Base {
private:
	i2c_port_t i2c_port;
	uint8_t device_addr;

public:
	I2C_Bus(i2c_port_t id,  int sda_pin, int sclk_pin, uint32_t baudrate, int rx_buffer_size, int tx_buffer_size)
	{
		i2c_port = id;

		i2c_config_t conf;
		conf.mode = I2C_MODE_MASTER;
		conf.sda_io_num = sda_pin;
		conf.scl_io_num = sclk_pin;
		conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
		conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
		conf.master.clk_speed = baudrate;

		i2c_param_config(i2c_port, &conf);
		i2c_driver_install(i2c_port, conf.mode, rx_buffer_size, tx_buffer_size, 0);
	};
	~I2C_Bus();

	int transfer(enum mode rw, uint8_t *tx_data, size_t txlen, uint8_t *rx_data, size_t rxlen, TickType_t ticks_to_wait = portMAX_DELAY) override
	{
		if (rw == Read) {
			return  i2c_master_write_to_device(i2c_port, device_addr, tx_data, txlen, ticks_to_wait);
		}
		else {
			return i2c_master_write_read_device(i2c_port, device_addr, tx_data, txlen, rx_data, rxlen, ticks_to_wait);
		}

		return 0;
	}
};
