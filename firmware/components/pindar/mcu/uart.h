#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"

class UART {
private:
	uart_port_t uart_id = -1;
	int rx_buffer_size = 0;
	int tx_buffer_size = 0;

public:
	UART(uart_port_t id,  int rx_pin, int tx_pin, uint32_t baudrate, int rx_size, int tx_size): uart_id(id), rx_buffer_size(rx_size), tx_buffer_size(tx_size)
	{
		uart_config_t uart_config = {0};
		uart_config.baud_rate = baudrate;
		uart_config.data_bits = UART_DATA_8_BITS;
		uart_config.parity = UART_PARITY_DISABLE;
		uart_config.stop_bits = UART_STOP_BITS_1;
		uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
		uart_config.source_clk = UART_SCLK_APB;

		uart_driver_install(uart_id, rx_buffer_size, tx_buffer_size, 0, NULL, 0);
		uart_param_config(uart_id, &uart_config);
		uart_set_pin(uart_id, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	};
	~UART();

	int write(const void *src, size_t size)
	{
		return uart_write_bytes(uart_id, src, size);
	};

	int read(void *src, size_t size, TickType_t ticks_to_wait)
	{
		return uart_read_bytes(uart_id, src, size, ticks_to_wait);
	};

};
