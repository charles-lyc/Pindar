#pragma once

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "mcu/spi.h"
#include "imu_sensor_base.h"
#include "bus.h"

class ADIS16460 : public imu_sensor_base {
private:
	Bus_Base *bus = nullptr;

public:
	ADIS16460(Bus_Base *bushw);
	~ADIS16460();

	int probe()override;
	int initialize() override;
	int read_raw_data(int32_t *gyro, int32_t *accel, int16_t *temp) override;
};
