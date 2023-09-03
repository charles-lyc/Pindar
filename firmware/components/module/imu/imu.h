#pragma once

#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "drivers/imu_sensor/imu_sensor_base.h"

struct quaternion {
	float w;
	float x;
	float y;
	float z;
};

struct SM_ImuData {
	char id[16] = "imu data";

	TickType_t timestamp;
	float gyro[3];
	float accel[3];
	float temperature;

	struct quaternion q;
	float euler_zyx[3];

	// queue;
};

enum IMU_AXIS {
	ROLL = 0,
	PITCH = 1,
	YAW = 2
};

class IMU_Module {
private:
	TickType_t timestamp;
	QueueHandle_t frame_event = nullptr;

	int32_t gyro_raw[3], accel_raw[3];
	int16_t temperature_raw[1];
	float gyro_smooth[3], accel_smooth[3], temperature_smooth;
	float gyro_scale[3], gyro_scale_default[3];
	float gyro_bias[3];
	float accel_scale[3], accel_scale_default[3];
	float accel_bias[3];

	bool run_gyro_static_calibr = false;
	bool run_gyro_scale_calibr = false;
	bool run_accel_calibr = false;

	float gyro[3];
	float accel[3];
	float temperature;
	struct quaternion q;
	float euler_zyx[3];

	QueueHandle_t data_queue;

	imu_sensor_base *interface = nullptr;
	// struct SM_ImuData *sm = nullptr;       // 共享内存通信（进程间通信，暂时不需要）

	void pre_process();
	void madgwick_update();

	/**
	 * @brief main process of IMU data
	 * @param pvParameters
	 */
	TaskHandle_t process_task_handle;
	void process_task(void *pvParameters);
	static void process_task_static(void *pvParameters)
	{
		IMU_Module *imu = static_cast<IMU_Module *>(pvParameters);
		imu->process_task(nullptr);
	}

	/**
	 * @brief set the constant bias of gyro
	 * @param en
	 * @return int
	 */
	TaskHandle_t gyro_static_calibr_task_handle;
	void gyro_static_calibr_task(void *pvParameters);

	/**
	 * @brief set the constant scale error of gyro z only
	 * @param en
	 * @return int
	 */
	TaskHandle_t gyro_z_scale_calibr_task_handle;
	void gyro_z_scale_calibr_task(void *pvParameters);
	TaskHandle_t aceel_sphere_calibr_task_handle;
	void aceel_sphere_calibr_task(void *pvParameters);

public:
	IMU_Module(imu_sensor_base *itf);
	~IMU_Module();

	TickType_t get_timestamp()
	{
		return timestamp;
	};
	void start_gyro_static_calibr()
	{
		run_gyro_static_calibr = true;
	};
	bool get_gyro_static_calibr_status()
	{
		return run_gyro_static_calibr;
	};
	void start_gyro_z_scale_calibr()
	{
		run_gyro_scale_calibr = true;
	};
	bool get_gyro_z_scale_calibr_status()
	{
		return run_gyro_scale_calibr;
	};
	void start_aceel_sphere_calibr()
	{
		run_accel_calibr = true;
	};
	bool get_accel_calibr_status()
	{
		return run_accel_calibr;
	};
	float get_gyro_x()
	{
		return gyro[ROLL];
	};
	float get_gyro_y()
	{
		return gyro[PITCH];
	};
	float get_gyro_z()
	{
		return gyro[YAW];
	};
	float get_accel_x()
	{
		return accel[ROLL];
	};
	float get_accel_y()
	{
		return accel[PITCH];
	};
	float get_accel_z()
	{
		return accel[YAW];
	};
	struct quaternion get_quaternion()
	{
		return q;
	};
	float get_euler_roll()
	{
		return (euler_zyx[ROLL] = atan2(2 * (q.w * q.x + q.y * q.z), -2 * (q.x * q.x + q.y * q.y) + 1));
	}
	float get_euler_pitch()
	{
		return (euler_zyx[PITCH] = asin(2 * (q.w * q.y - q.z * q.x)));
	}
	float get_euler_yaw()
	{
		return (euler_zyx[YAW] = atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z)));
	}
	// float get_attitude(float);

	/**
	 * @brief trigged in gpio isr or timer
	 * @param arg
	 */
	void frame_event_isr(void *arg);
	static void frame_event_isr_static(void *pvParameters)
	{
		IMU_Module *imu = static_cast<IMU_Module *>(pvParameters);
		imu->frame_event_isr(nullptr);
	}
};
