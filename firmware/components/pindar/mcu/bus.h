#pragma once

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

class Bus_Base {
public:
	enum mode {
		Write = 0,
		Read = 1,
	};

	~Bus_Base() {};

	// polling or block to wait for transfer result
	virtual int transfer(enum mode rw, uint8_t *tx_data, size_t txlen, uint8_t *rx_data, size_t rxlen, TickType_t ticks_to_wait = portMAX_DELAY)
	{
		return -1;
	};

	// non-blocking transfer
	virtual int transfer_request(enum mode rw, uint8_t *tx_data, size_t txlen, uint8_t *rx_data, size_t rxlen, TickType_t ticks_to_wait = portMAX_DELAY)
	{
		return -1;
	};
};
