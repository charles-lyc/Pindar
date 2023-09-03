#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "pindar_config.h"
#include "mcu/gpio.h"

#include "module/servo/dc_servo.h"

class DC_Servo_4WD {
private:

protected:

    // DC_Servo *motor_1;
    // DC_Servo *motor_2;
    // DC_Servo *motor_3;
    // DC_Servo *motor_4;

public:
	// on board imu bus and GPIO_Normal
	DC_Servo_4WD()
	{
		// motor_1 = new DC_Servo(PINDAR_GPIO_1, PINDAR_GPIO_2, PINDAR_GPIO_9);
		// motor_2 = new DC_Servo(PINDAR_GPIO_3, PINDAR_GPIO_4, PINDAR_GPIO_10);
		// motor_3 = new DC_Servo(PINDAR_GPIO_5, PINDAR_GPIO_6, PINDAR_GPIO_11);
		// motor_4 = new DC_Servo(PINDAR_GPIO_7, PINDAR_GPIO_8, PINDAR_GPIO_12);


	};

	~DC_Servo_4WD()
	{
		;
	};

};
