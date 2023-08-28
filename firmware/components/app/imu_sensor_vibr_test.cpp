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

	// dc_motor = new DC_Motor_Driver(gpio_1, gpio_2);
	// dc_module = new DC_Motor_Module(dc_motor);

	xTaskCreate(process_task_static, "scan_task", 4096, this, 5, NULL);
	xTaskCreate(upload_task_static, "upload_task", 4096, this, 5, NULL);

	CPU_Monitor::get_instance()->start();
}

IMU_Sensor_Vibr_Test::~IMU_Sensor_Vibr_Test()
{
}


void IMU_Sensor_Vibr_Test::upload_task(void *pvParameters)
{
	while (true) {

		icm_42688_external->read_raw_data(datapack.gyro_raw, datapack.accel_raw, &datapack.temp);

		datapack.header = 0xA5;
		datapack.timestamp = GetTick();
		datapack.crc = crc();

		serial.transmit(&datapack);

		vTaskDelay(1 / portTICK_PERIOD_MS);
	}
}

// 仅需上位机调整扫频频率
void IMU_Sensor_Vibr_Test::process_task(void *pvParameters)
{
	// dc_module.set_duty_cycle(0.5);

	while (true) {

		if (serial.receive(buffer, sizeof(buffer), portMAX_DELAY)) {

			// dc_module.set_frequency(freq);

		}
	}
}

