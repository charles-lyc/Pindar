#pragma once

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "mcu/spi.h"
#include "imu_sensor_base.h"
#include "bus.h"

class ICM42688 : public imu_sensor_base {
private:
	Bus_Base *bus = nullptr;

public:
	ICM42688(Bus_Base *bushw);
	~ICM42688();

	int probe()override;
	int initialize() override;
	int read_raw_data(int32_t *gyro, int32_t *accel, int16_t *temp) override;
};
