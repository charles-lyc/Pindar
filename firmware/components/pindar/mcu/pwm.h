#pragma once

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
#include "esp_log.h"

#include "driver/pulse_cnt.h"
#include "driver/ledc.h"

class PWM_Input {
	enum Mode {
		Counts = 0,
		Interval,   // more performance but costs lots of cpu
	};
private:
	pcnt_unit_handle_t pcnt_unit = NULL;
	enum Mode mode;

public:
	PWM_Input(gpio_num_t io_1, gpio_num_t io_2, enum Mode m = Counts): mode(m)
	{

	}
	PWM_Input(gpio_num_t io, enum Mode m = Counts): mode(m)
	{
		pcnt_unit_config_t unit_config = {0};
		unit_config.high_limit = INT16_MAX,
		unit_config.low_limit = INT16_MIN,
		unit_config.flags.accum_count = 1,
		pcnt_new_unit(&unit_config, &pcnt_unit);

		pcnt_glitch_filter_config_t filter_config = {
			.max_glitch_ns = 100,
		};
		pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config);

		pcnt_chan_config_t chan_a_config = {
			.edge_gpio_num = io,
			.level_gpio_num = -1,
		};
		pcnt_channel_handle_t pcnt_chan = NULL;
		pcnt_new_channel(pcnt_unit, &chan_a_config, &pcnt_chan);

		pcnt_channel_set_edge_action(pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE);
		pcnt_channel_set_level_action(pcnt_chan, PCNT_CHANNEL_LEVEL_ACTION_INVERSE, PCNT_CHANNEL_LEVEL_ACTION_INVERSE);

		int watch_points[] = {unit_config.high_limit, unit_config.low_limit};
		for (size_t i = 0; i < sizeof(watch_points) / sizeof(watch_points[0]); i++) {
			pcnt_unit_add_watch_point(pcnt_unit, watch_points[i]);
		}

		pcnt_unit_enable(pcnt_unit);
		pcnt_unit_clear_count(pcnt_unit);
		pcnt_unit_start(pcnt_unit);
	}

	~PWM_Input()
	{

	}

	int get_count()
	{
		int pulse_count;
		pcnt_unit_get_count(pcnt_unit, &pulse_count);
		return pulse_count;
	}

	uint32_t get_edge_interval()
	{
		return 0;
	}

};

class PWM_Output {
private:
	ledc_timer_t timer_num = LEDC_TIMER_0;
	ledc_channel_t channel = LEDC_CHANNEL_0;
	uint32_t full_scale = (1 << 10) - 1;

public:
	PWM_Output(int io, uint32_t freq_hz)
	{
		// use ledc to generate pwm
		// Prepare and then apply the LEDC PWM timer configuration
		ledc_timer_config_t ledc_timer = {
			.speed_mode       = LEDC_LOW_SPEED_MODE,
			.duty_resolution  = LEDC_TIMER_10_BIT,
			.timer_num        = timer_num,
			.freq_hz          = 200,
			.clk_cfg          = LEDC_AUTO_CLK
		};
		ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

		// Prepare and then apply the LEDC PWM channel configuration
		ledc_channel_config_t ledc_channel = {
			.gpio_num       = io,
			.speed_mode     = LEDC_LOW_SPEED_MODE,
			.channel        = channel,
			.intr_type      = LEDC_INTR_DISABLE,
			.timer_sel      = timer_num,
			.duty           = 0, // Set duty to 0%
			.hpoint         = 0
		};
		ledc_channel_config(&ledc_channel);


		// ledc_stop(LEDC_LOW_SPEED_MODE, channel, 1);

		// if (++channel >= LEDC_CHANNEL_MAX) {
		//  inttimer_num++;
		// }
	}
	~PWM_Output()
	{

	}

	void start()
	{
		ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, channel, 0.5 * (2 ^ 10), 0);
	}

	void set_freq_hz(uint32_t freq_hz)
	{
		ledc_set_freq(LEDC_LOW_SPEED_MODE, timer_num, freq_hz);
	}

	// duty: 0 ~ 1000
	void set_duty_cycle(float duty)
	{
		ESP_LOGI("PWM_Output", "full_scale: %d", (int)full_scale);
		ESP_LOGI("PWM_Output", "ledc_set_duty: %d", (int)(duty * full_scale));
		ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, duty * full_scale);
	}
};
