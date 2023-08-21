#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include "pindar.h"
#include "imu_module.h"

#include "icm42688.h"

class IMU_Sensor_Vibr_Test : public Pindar
{
private:
    // DC_Motor *motor;

    // Param_Float test;

public:
    IMU_Sensor_Vibr_Test();
    ~IMU_Sensor_Vibr_Test();

    ICM42688 *icm_42688;
    IMU_Module *imu_module;

    int demo_imu_sensor_vibration_scan(void);
};
