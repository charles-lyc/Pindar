#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/i2c.h"

class I2C_Bus
{
private:
    i2c_port_t i2c_port;

public:
    I2C_Bus(i2c_port_t id,  int sda_pin, int sclk_pin, uint32_t baudrate, int rx_buffer_size, int tx_buffer_size)
    {
        i2c_port = id;

        i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = sda_pin,
            .scl_io_num = sclk_pin,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = baudrate,
        };

        i2c_param_config(i2c_port, &conf);

        return i2c_driver_install(i2c_port, conf.mode, rx_buffer_size, tx_buffer_size, 0);
    };
    ~I2C_Bus();

    int bus_transfer_polling(bool rw, uint8_t *tx_data, uint8_t *rx_data, size_t len);
    int bus_transfer(bool rw, uint8_t *tx_data, uint8_t *rx_data, size_t len, TickType_t ticks_to_wait = max)
    {
        if (rw == read)
        {
            return i2c_master_write_read_device(i2c_port, MPU9250_SENSOR_ADDR, &reg_addr, 1, data, len, ticks_to_wait);
        }
        else
        {
            uint8_t write_buf[2] = {reg_addr, data};
            return  i2c_master_write_to_device(i2c_port, MPU9250_SENSOR_ADDR, write_buf, sizeof(write_buf), ticks_to_wait);
        }

    }

};
