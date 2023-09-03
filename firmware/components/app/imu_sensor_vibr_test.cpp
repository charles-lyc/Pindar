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
	pwmout = new PWM_Output(PINDAR_GPIO_1, 200);
	gpio_2 = new GPIO_Normal(PINDAR_GPIO_2, GPIO_Normal::DIGTAL_INnOUTPUT);


	// xTaskCreate(process_task_static, "scan_task", 4096, this, 5, NULL);
	xTaskCreate(upload_task_static, "upload_task", 4096, this, 5, NULL);

	// CPU_Monitor::get_instance()->start();
}

IMU_Sensor_Vibr_Test::~IMU_Sensor_Vibr_Test()
{
}

void IMU_Sensor_Vibr_Test::upload_task(void *pvParameters)
{
	pwmout->set_duty_cycle(0.5);

	while (true) {

		icm_42688_external->read_raw_data(datapack.gyro_raw, datapack.accel_raw, &datapack.temp);

		// datapack.header = 0xAA;
		// datapack.timestamp = xTaskGetTickCount();
		// // datapack.crc = crc();
		// std::array<uint8_t, sizeof(datapack)> buffer;
		// memcpy(buffer.data(), &datapack, sizeof(datapack));
		// std::cout << buffer << std::endl;

		// std::vector<int16_t> values{ 1, 2, 3, 4, 5, 6, 7 };
		// uint16_t crc = 0xffff;

		// std::vector<uint8_t> data{ 0xaa, 0xaa };
		// data.push_back(static_cast<uint8_t>(datapack.timestamp & 0xff));
		// data.push_back(static_cast<uint8_t>((datapack.timestamp >> 8) & 0xff));
		// data.push_back(static_cast<uint8_t>((datapack.timestamp >> 16) & 0xff));
		// data.push_back(static_cast<uint8_t>((datapack.timestamp >> 24) & 0xff));
		// for (auto value : values) {
		//  data.push_back(static_cast<uint8_t>(value & 0xff));
		//  data.push_back(static_cast<uint8_t>((value >> 8) & 0xff));
		// }
		// data.push_back(static_cast<uint8_t>(crc & 0xff));
		// data.push_back(static_cast<uint8_t>((crc >> 8) & 0xff));

		// for (auto byte : data) {
		//  std::cout << std::hex << static_cast<int>(byte);
		// }

		gpio_2->toggle();
		ESP_LOGI("IMU_Sensor_Vibr_Test", "gpio_2: %d", gpio_2->get());

		// ESP_LOGI("IMU_Sensor_Vibr_Test", "pwm in count: %d", pwmin->get_count());

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

// 仅需上位机调整扫频频率
void IMU_Sensor_Vibr_Test::process_task(void *pvParameters)
{
	// dc_module.set_duty_cycle(0.5);

	while (true) {

		// if (serial.receive(buffer, sizeof(buffer), portMAX_DELAY)) {

		// dc_module.set_frequency(freq);

		// }
	}
}

