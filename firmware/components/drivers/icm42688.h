#pragma once

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "spi.h"
#include "imu_sensor_interface.h"

class ICM42688 : public IMU_Interface {
private:
	SPI_Interface *interface = nullptr;

public:
	ICM42688(SPI_Interface *spi_interface);
	~ICM42688();

	int probe()override;
	int initialize() override;
	int read_raw_data(int32_t *gyro, int32_t *accel, int16_t *temp) override;
};
