#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_log.h"
#include "esp_system.h"

#include "imu_sensor_vibr_test.h"

// main 只提供一个入口和临时环境光用来实例化具体项目app
// 不需要给demo app注入接口，本项目开放给app所有的底层，适合直接由这些app自行选择和配置驱动
extern "C" void app_main(void)
{
	try {
		// demo: imu sensor vibration scanning test
		IMU_Sensor_Vibr_Test *demo = new IMU_Sensor_Vibr_Test();

		// 4WD mechanical wheal
		// MecanumWhealDrive *demo = new MecanumWhealDrive();

		// 3WD omni wheels
		// demo_3wd_omni_wheels();

		// lcd
		// demo_lcd();

		// pmw3360 driver
		// demo_pmw3360();

		// flight controller
		// demo_fc();
	}
	catch (const std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
}
