#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"

#include "pindar.h"

#include "mcu/pwm.h"
#include "mcu/gpio.h"
#include "drivers/imu_sensor/icm42688.h"
#include "drivers/serial.h"
#include "drivers/pulse_gen.h"

#include "module/imu/imu.h"
#include "module/cpu_monitor.h"
#include "module/servo/dc_servo.h"

#include "pindar/dc_motor_4wd.h"

class IMU_Sensor_Vibr_Test : public Pindar {

private:
#pragma pack(push, 1)
	struct DataPack {
		uint8_t header;
		uint32_t timestamp;
		int32_t gyro_raw[3];
		int32_t accel_raw[3];
		int16_t temp;
		uint16_t crc;
	} datapack;
#pragma pack(pop)

	ICM42688 *icm_42688_external;
	IMU_Module *imu_module;
	// PulseGen *pulse_gen;
	PWM_Output *pwmout;
	PWM_Input *pwmin;
	GPIO_Normal *gpio_2;

	uint16_t crc16(const uint8_t *data, size_t length);

	void upload_task(void *pvParameters);
	static void upload_task_static(void *pvParameters)
	{
		IMU_Sensor_Vibr_Test *i = static_cast<IMU_Sensor_Vibr_Test *>(pvParameters);
		i->upload_task(nullptr);
	}
	void process_task(void *pvParameters);
	static void process_task_static(void *pvParameters)
	{
		IMU_Sensor_Vibr_Test *i = static_cast<IMU_Sensor_Vibr_Test *>(pvParameters);
		i->process_task(nullptr);
	}

public:
	IMU_Sensor_Vibr_Test();
	~IMU_Sensor_Vibr_Test();
};
