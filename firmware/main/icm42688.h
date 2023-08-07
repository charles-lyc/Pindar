#pragma once

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

extern "C"
{

    /**
     * @brief init
     * @return 0: success; -1: fail
     */
    int icm42688_init(struct imu_sensor_interface *interface);

    /**
     * @brief read icm42688 raw data
     * @param timestamp
     * @param gyro
     * @param acc
     * @return 0: success; -1: fail
     */
    int icm42688_read(struct imu_sensor_interface *interface, TickType_t *timestamp, int32_t *gyro, int32_t *accel, int32_t *temp);
}
