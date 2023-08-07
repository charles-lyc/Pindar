#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

#include "imu.h"

IMU_Module::IMU_Module(struct imu_sensor_interface &itf)
{
    interface = itf;
    interface.init(&interface);

    // stored value or reset defalut value
    // gyro_scale = spifs_read

    xTaskCreate(process_task, "process_task", 4096, this, 5, NULL);
    xTaskCreate(convert_task, "convert_task", 4096, this, 5, NULL);
    xTaskCreate(obs_covariant_task, "obs_covariant_task", 4096, this, 5, NULL);
}

IMU_Module::~IMU_Module()
{
    interface.deinit();

    xTaskDelete();
    xSemaphoreDelete();
}

// 中断产生一个信号量，process线程开始工作

void IMU_Module::process_task(void *pvParameters)
{
    TickTypes_t timestamp;
    int16_t gyro_raw[3];
    int16_t accel_raw[3];
    int16_t temperature[1];

    while (1)
    {
        if (xSemaphoreTake(interface.frame_event, portMAX_DELAY) == pdTRUE)
        {
            if (interface.read(&interface, &timestamp, gyro_raw, accel_raw))
            {
                ESP_LOG_ERROR(TAG, "read failed");
                continue;
            }

            // lpf?

            mem_imu_data.timestamp = timestamp;
            mem_imu_data.temperature = temperature;
            for (size_t i = 0; i < 3; i++)
            {
                mem_imu_data.gyro[i] = (gyro_raw[i] - gyro_bias[i]) * gyro_scale[i];
                mem_imu_data.accel[i] = (accel_raw[i] - accel_bias[i]) * accel_scale[i];
            }
        }
    }
}

void IMU_Module::convert_task(void *pvParameters)
{
    int16_t gyro[3] = {0, 0, 0};
    int16_t acc[3] = {0, 0, 0};
    int32_t timestamp = 0;
    while (1)
    {
        quaternion_to_euler();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void IMU_Module::calibrate_task(void *pvParameters)
{
    while (1)
    {
    }
}
