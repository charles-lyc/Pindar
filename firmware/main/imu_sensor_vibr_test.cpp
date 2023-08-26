#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include "pindar_config.h"
#include "pindar.h"
#include "imu_sensor_vibr_test.h"

IMU_Sensor_Vibr_Test::IMU_Sensor_Vibr_Test()
{
	// exteral imu sensor
	icm_42688 = new ICM42688(spi2_bus);
	imu_module = new IMU_Module(icm_42688);
	gpio_imu->set_callback(&imu_module->frame_event_isr_static, &imu_module);

	// icm_42688 = new ICM42688(spi2_bus);
	// imu_module = new IMU_Module(icm_42688);  // timer.set_frequency(1000);
	// timer.set_callback(&imu_module->frame_event_isr_static, &imu_module);

	// dc_motor = new DC_Motor_Driver(gpio_1, gpio_2);
	// dc_module = new DC_Motor_Module(dc_motor);

	xTaskCreate(scan_task_static, "scan_task", 4096, this, 5, NULL);
	xTaskCreate(record_task_static, "record_task", 4096, this, 5, NULL);

	CPU_Monitor::get_instance()->start();
}

IMU_Sensor_Vibr_Test::~IMU_Sensor_Vibr_Test()
{
}


void IMU_Sensor_Vibr_Test::scan_task(void *pvParameters)
{
	// dc_module.set_duty_cycle(0.5);

	while (true) {
		for (size_t freq = 1 * 1000; freq < 20 * 1000; freq++) {
			// dc_module.set_frequency(freq);
			vTaskDelay(1 / portTICK_PERIOD_MS);
		}
	}
}

void IMU_Sensor_Vibr_Test::record_task(void *pvParameters)
{
	while (true) {
		// read and transfer to serial port
		// interface->read_raw_data(datapack.gyro_raw, datapack.accel_raw, &datapack.temp);

		// datapack.header = 0xA5;
		// datapack.timestamp = GetTick();
		// datapack.crc = crc();

		// serial1.transmit(&datapack);

		vTaskDelay(1 / portTICK_PERIOD_MS);
	}
}


// 方法一：使用静态中间函数并传递实例
// 方法二：使用std::bind
// #include <iostream>
// #include <functional>
//     // 假设有一个 GPIO_ISR_T 类型的定义，用于代表 GPIO 中断函数类型
//     using gpio_isr_t = void (*)(void *);
//     class GPIOInterrupt
//     {
//     public:
//         void set_callback(gpio_isr_t isr, void *arg = nullptr)
//         {
//             callback_ = std::bind(isr, arg); // 使用 std::bind 绑定函数指针和参数
//         }
//         void trigger_interrupt()
//         {
//             if (callback_)
//             {
//                 callback_();
//             }
//         }
//     private:
//         std::function<void()> callback_;
//     };
//     class IMU_Module
//     {
//     public:
//         void frame_event_isr()
//         {
//             std::cout << "IMU frame event ISR triggered" << std::endl;
//         }
//     };
//     int main()
//     {
//         GPIOInterrupt *imu_frame_intr = new GPIOInterrupt();
//         IMU_Module *imu_module = new IMU_Module();
//         imu_frame_intr->set_callback(std::bind(&IMU_Module::frame_event_isr, imu_module));
//         // 模拟触发 GPIO 中断，从而触发回调
//         imu_frame_intr->trigger_interrupt();
//         delete imu_frame_intr;
//         delete imu_module;
//         return 0;
//     }
// 方法三：lambda表达式
// imu_frame_intr->set_callback(CALLBACK_LAMBDA_VOID(IMU_Module, frame_event_isr), imu_module);
// imu_frame_intr->set_callback([imu_module](void *param)
//                              { static_cast<IMU_Module *>(param)->frame_event_isr(param); },
//                              nullptr);
