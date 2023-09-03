#include "driver/pcnt.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#include "dc_servo.h"
#include "param.h"

DC_Servo::DC_Servo(gpio_num_t pin_motor_a,
                   gpio_num_t pin_motor_b,
                   gpio_num_t pin_enc)
{

	

	xTaskCreate(&pos_ctrl_task_static, "pos_ctrl_task", 1024, this, 3, &pos_ctrl_task_handle);
	xTaskCreate(&rate_ctrl_task_static, "rate_ctrl_task", 1024, this, 3, &rate_ctrl_task_handle);
	xTaskCreate(&torque_ctrl_task_static, "torque_ctrl_task", 1024, this, 3, &torque_ctrl_task_handle);

}

DC_Servo::~DC_Servo()
{

}

void DC_Servo::pos_ctrl_task(void *pvParameters)
{
	while (1) {
		// xSemaphoreTake(frame_event, 1);
		{

		}
	}
}

void DC_Servo::rate_ctrl_task(void *pvParameters)
{
	while (1) {
		// xSemaphoreTake(frame_event, 1);
		{

		}
	}
}

void DC_Servo::torque_ctrl_task(void *pvParameters)
{
	while (1) {
		// xSemaphoreTake(frame_event, 1);
		{

		}
	}
}

// void DC_Servo::pcnt_int(void)
// {
//     // rotary_encoder_t *encoder;               // PCNT rotary encoder handler

// 	// /* Rotary encoder underlying device is represented by a PCNT unit in this example */
// 	// uint32_t pcnt_unit = 0;
// 	// /* Create rotary encoder instance */
// 	// rotary_encoder_config_t config = ROTARY_ENCODER_DEFAULT_CONFIG((rotary_encoder_dev_t)pcnt_unit, GPIO_PCNT_PINA, GPIO_PCNT_PINB);
// 	// rotary_encoder_new_ec11(&config, &motor_ctrl.encoder);
// 	// /* Filter out glitch (1us) */
// 	// motor_ctrl.encoder->set_glitch_filter(motor_ctrl.encoder, 1);
// 	// /* Start encoder */
// 	// motor_ctrl.encoder->start(motor_ctrl.encoder);
// 	// pcnt_counter_clear((pcnt_unit_t)pcnt_unit);
// }