#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"


class Servo_Base {
protected:
	float angle_pos, target_angle_pos;
	uint32_t pos_ctrl_rate = 50;
	// pid *pid;

	float rpm, target_rpm;
	uint32_t rpm_ctrl_rate = 100;
	// pid *pid;

	float torque, target_torque;
	uint32_t torq_ctrl_rate = 1000;
	// pid *pid;

	float pulse_freq = 10 * 1000;
	bool brake;
	uint32_t circle_count;


	TaskHandle_t pos_ctrl_task_handle;
	virtual void pos_ctrl_task(void *pvParameters) = 0;
	static void pos_ctrl_task_static(void *pvParameters)
	{
		Servo_Base *servo = static_cast<Servo_Base *>(pvParameters);
		servo->pos_ctrl_task(nullptr);
	}

	TaskHandle_t rate_ctrl_task_handle;
	virtual void rate_ctrl_task(void *pvParameters) = 0;
	static void rate_ctrl_task_static(void *pvParameters)
	{
		Servo_Base *servo = static_cast<Servo_Base *>(pvParameters);
		servo->rate_ctrl_task(nullptr);
	}

	TaskHandle_t torque_ctrl_task_handle;
	virtual void torque_ctrl_task(void *pvParameters) = 0;
	static void torque_ctrl_task_static(void *pvParameters)
	{
		Servo_Base *servo = static_cast<Servo_Base *>(pvParameters);
		servo->torque_ctrl_task(nullptr);
	}
public:

	Servo_Base()
	{

	}

	~Servo_Base()
	{
		// vTaskDelete(task_handle);
	}

	int set_pulse_freq(float freq)
	{
		pulse_freq = freq;
		return 0;
	}
	float get_pulse_freq()
	{
		return pulse_freq;
	}
	// pos can range from -∞ to +∞
	int set_angle_pos(float pos)
	{
		target_angle_pos = pos;
		return 0;
	}
	float get_angle_pos()
	{
		return angle_pos;
	}
	int set_rate(float rate)
	{
		target_rpm = rate;
		return 0;
	}
	float get_rate()
	{
		return rpm;
	}
	// set torque (current)
	int set_torque(float torque)
	{
		target_torque = torque;
		return 0;
	}
	float get_torque()
	{
		return torque;
	}
	// set pwm (voltage), quicker than set_torque definitly, but dangerous
	virtual int set_pwm(float pwm)
	{
		// io set pwm ()
		return 0;
	}	
	int set_brake(bool en)
	{
		brake = en;
		return 0;
	}
};
