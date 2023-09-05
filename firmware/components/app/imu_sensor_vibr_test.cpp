#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"

#include "imu_sensor_vibr_test.h"


IMU_Sensor_Vibr_Test::IMU_Sensor_Vibr_Test()
{
	// exteral imu sensor
	icm_42688_external = new ICM42688(spi3_bus);
	// imu_module = new IMU_Module(icm_42688_external);
	// gpio_imu->set_callback(&imu_module->frame_event_isr_static, &imu_module);

	pwmin = new PWM_Input(PINDAR_GPIO_9);
	pwmout = new PWM_Output(PINDAR_GPIO_1, 200, 0.5);
	gpio_2 = new GPIO_Normal(PINDAR_GPIO_2, GPIO_Normal::DIGTAL_INnOUTPUT, 0);


	xTaskCreate(process_task_static, "scan_task", 4096, this, 5, NULL);
	xTaskCreate(upload_task_static, "upload_task", 4096, this, 5, NULL);

	// CPU_Monitor::get_instance()->start();
}

IMU_Sensor_Vibr_Test::~IMU_Sensor_Vibr_Test()
{
}

void IMU_Sensor_Vibr_Test::upload_task(void *pvParameters)
{
	while (true) {

		datapack.header = 0xAA;
		icm_42688_external->read_raw_data(datapack.gyro_raw, datapack.accel_raw, &datapack.temp);
		datapack.timestamp = xTaskGetTickCount();
		datapack.crc = crc16((const uint8_t *)&datapack, sizeof(datapack) - 2);

		// std::cout << "datapack sensor: " <<datapack.gyro_raw[0] << " " << datapack.gyro_raw[1] << " " << datapack.gyro_raw[2] << " " <<
		//           datapack.accel_raw[0] << " " << datapack.accel_raw[1] << " " << datapack.accel_raw[2] << " " <<
		//           datapack.temp << std::endl;

		uart1->write((const uint8_t *)&datapack, sizeof(datapack));

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

uint16_t IMU_Sensor_Vibr_Test::crc16(const uint8_t *data, size_t length)
{
	uint8_t x;
	uint16_t crc = 0xFFFF;

	while (length--) {
		x = crc >> 8 ^ *data++;
		x ^= x >> 4;
		crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x << 5)) ^ ((uint16_t)x);
	}
	return crc;
}

// 仅需上位机调整扫频频率
void IMU_Sensor_Vibr_Test::process_task(void *pvParameters)
{
	// dc_module.set_duty_cycle(0.5);
	uint32_t freq = 200;
	TickType_t xLastWakeTime;
	const TickType_t period = pdMS_TO_TICKS(10);
	BaseType_t xWasDelayed;

	xLastWakeTime = xTaskGetTickCount();

	while (true) {

		// if (serial.receive(buffer, sizeof(buffer), portMAX_DELAY)) {

		pwmout->set_freq_hz(freq);
		if (freq++ > 1000) {
			freq = 200;
		}

		// Wait for the next cycle.
		xWasDelayed = xTaskDelayUntil(&xLastWakeTime, period);
		// Perform action here. xWasDelayed value can be used to determine
		// whether a deadline was missed if the code here took too long.

	}
}

