/**
 * @file imu_sensor_interface.h
 * @brief low level 的imu抽象接口（handler）
 * @author chaoz (charles-lyc@outlook.com)
 * @version 0.1
 * @date 2023-08-07
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"

#include "driver/gpio.h"

struct imu_sensor_interface
{
    // 接口自理
    int (*init)(struct imu_sensor_interface *interface);
    int (*deinit)(struct imu_sensor_interface *interface);
    int (*read)(struct imu_sensor_interface *interface, TickType_t *timestamp, int16_t *gyro, int16_t *accel, int16_t *temp);

    float gyro_lsb;
    float accel_lsb;
    int gyro_full_scale_dps;
    int accel_full_scale_g;

    int output_data_rate;

    TickType_t timestamp;
    SemaphoreHandle_t frame_event;
    gpio_num_t frame_intr_io_num;
};
