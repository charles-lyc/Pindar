#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_log.h"

#include "servo_base.h"

class DC_Servo : public Servo_Base {
private:


public:
	DC_Servo(gpio_num_t pin_motor_a,
	         gpio_num_t pin_motor_b,
	         gpio_num_t pin_enc);
	~DC_Servo();

	void pos_ctrl_task(void *pvParameters) override;
	void rate_ctrl_task(void *pvParameters) override;
	void torque_ctrl_task(void *pvParameters) override;
};
