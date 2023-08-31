#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "pindar_config.h"
#include "mcu/gpio.h"

class DC_Motor_4WD {
private:

protected:

    DC_Motor *motor_1;
    DC_Motor *motor_2;
    DC_Motor *motor_3;
    DC_Motor *motor_4;

public:
	// on board imu bus and GPIO_Normal
	DC_Motor_4WD()
	{
		motor_1 = new DC_Motor(PINDAR_GPIO_1, PINDAR_GPIO_2, PINDAR_GPIO_9);
		motor_2 = new DC_Motor(PINDAR_GPIO_3, PINDAR_GPIO_4, PINDAR_GPIO_10);
		motor_3 = new DC_Motor(PINDAR_GPIO_5, PINDAR_GPIO_6, PINDAR_GPIO_11);
		motor_4 = new DC_Motor(PINDAR_GPIO_7, PINDAR_GPIO_8, PINDAR_GPIO_12);

        // motor.set_position/set_speed/set_torque?/set_freq/set_duty/set_pid/set_brake/

	};

	~DC_Motor_4WD()
	{
		;
	};

};
