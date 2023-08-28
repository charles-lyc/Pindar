#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

class SPI_Bus {
private:
	spi_device_handle_t handle;

public:
	enum RW {
		READ,
		WRITE
	};

	SPI_Bus(spi_host_device_t host_id, gpio_num_t cs, gpio_num_t sclk, gpio_num_t mosi, gpio_num_t miso, uint8_t spi_mode, int freq)
	{
		spi_bus_config_t buscfg = {
			.mosi_io_num = mosi,
			.miso_io_num = miso,
			.sclk_io_num = sclk,

			.quadwp_io_num = -1,
			.quadhd_io_num = -1,

			// .data4_io_num = -1,
			// .data5_io_num = -1,
			// .data6_io_num = -1,
			// .data7_io_num = -1,

			.max_transfer_sz = 64,
			// .flags = SPICOMMON_BUSFLAG_MASTER,
			// .intr_flags = 0,
		};
		spi_device_interface_config_t devcfg = {
			// .command_bits = 0,
			// .address_bits = 0,
			// .dummy_bits = 0,
			.mode = spi_mode,
			// .duty_cycle_pos = 0,
			// .cs_ena_pretrans = 0,
			// .cs_ena_posttrans = 0,

			.clock_speed_hz = freq,
			// .input_delay_ns = 0,
			.spics_io_num = cs,

			.flags = SPI_DEVICE_NO_DUMMY,
			.queue_size = 1,

			.pre_cb = nullptr,
			.post_cb = nullptr,
		};
		if (spi_bus_initialize(host_id, &buscfg, SPI_DMA_CH_AUTO) != ESP_OK) {
			ESP_LOGE("SPI", "spi_bus_initialize failed");
			return;
		}
		if (spi_bus_add_device(host_id, &devcfg, &handle) != ESP_OK) {
			ESP_LOGE("SPI", "spi_bus_add_device failed");
			return;
		}
	};

	~SPI_Bus()
	{
		// spi_bus_remove_device(handle);
		// spi_bus_free(host_id);
	}

	int bus_transfer_polling(bool rw, uint8_t *tx_data, uint8_t *rx_data, size_t len)
	{
		esp_err_t ret;
		spi_transaction_t t = {
			.flags = 0,
			.cmd = 0,
			.addr = 0,
			.user = nullptr,
			.tx_buffer = tx_data,
			.rx_buffer = rx_data,
		};

		if (rw == READ) {
			tx_data[0] |= 0x80;
			t.length = 8 * len;
			t.rxlength = 8 * len;
		}
		else {
			t.length = 8 * len;
			t.rxlength = 0;
		}

		ret = spi_device_polling_transmit(handle, &t);
		assert(ret == ESP_OK);

		return 0;
	};
};
