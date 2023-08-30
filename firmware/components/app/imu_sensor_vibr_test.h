#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"

#include "pindar.h"
#include "icm42688.h"

#include "imu.h"
#include "cpu_monitor.h"


class IMU_Sensor_Vibr_Test : public Pindar
{
private:
    struct DataPack{
        uint8_t header;
        uint32_t timestamp;
        int32_t gyro_raw[3];
        int32_t accel_raw[3];
        int16_t temp;
        uint16_t crc;
    } datapack;

    ICM42688 *icm_42688_external;
    // IMU_Module *imu_module;
    // DC_Motor *dc_motor;
    // DC_Motor_Module *dc_motor_module;

    void upload_task(void *pvParameters);
    static void upload_task_static(void *pvParameters){
        IMU_Sensor_Vibr_Test *i = static_cast<IMU_Sensor_Vibr_Test *>(pvParameters);
        i->upload_task(nullptr);
    }
    void process_task(void *pvParameters);
    static void process_task_static(void *pvParameters){
        IMU_Sensor_Vibr_Test *i = static_cast<IMU_Sensor_Vibr_Test *>(pvParameters);
        i->process_task(nullptr);
    }

public:
    IMU_Sensor_Vibr_Test();
    ~IMU_Sensor_Vibr_Test();
};
