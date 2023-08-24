#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include "pindar_config.h"
#include "imu_module.h"
#include "imu_sensor_interface.h"
#include "param.h"

IMU_Module::IMU_Module(IMU_Interface *itf)
{
    interface = itf;

    if (interface->probe())
    {
        // throw std::invalid_argument("Value must be positive");
    }
    interface->initialize();

    // create shared memory in iram
    // sm_data = (struct SM_ImuData *)malloc(sizeof(struct SM_ImuData));

    // Note: 正在尝试直接将成员函数作为任务函数传递，而成员函数具有额外的隐式参数（即 this 指针），导致类型不匹配。这里的process_task方法是一个非静态成员函数，而非静态成员函数在调用时需要通过一个实例来访问
    // 方法一：使用静态中间函数并传递实例，这里其实是强行利用了xTaskCreate()可以给task带参这个设定，把实例当作参数传递进去
    xTaskCreate(&IMU_Module::process_task_static, "process_task", 4096, this, 3, &process_task_handle);
    // 方法二：使用std::bind
    // 方法三：lambda表达式（类似方法一）
    // xTaskCreate(CALLBACK_LAMBDA_VOID(IMU_Module, process_task), "process_task", 4096, this, 3, &process_task_handle);

}

IMU_Module::~IMU_Module()
{
    // interface.deinit(&interface);

    // xTaskDelete();
    // xSemaphoreDelete();
}

void IMU_Module::frame_event_isr(void *arg)
{
    timestamp = xTaskGetTickCountFromISR();
    xSemaphoreGiveFromISR(frame_event, NULL);
}

void IMU_Module::process_task(void *pvParameters)
{
    int16_t gyro_raw[3];
    int16_t accel_raw[3];
    int16_t temperature_raw[1];
    float gyro_smooth[3];
    float accel_smooth[3];

    while (1)
    {
        if (xSemaphoreTake(frame_event, portMAX_DELAY) == pdTRUE)
        {
            // ll read
            interface->read_raw_data(gyro_raw, accel_raw, temperature_raw);
            {
                ESP_LOGE("IMU Module", "read failed");
                continue;
            }

            // lpf
            for (size_t i = 0; i < 3; i++)
            {
                gyro_smooth[i] = gyro_raw[i];
                accel_smooth[i] = accel_raw[i];
            }

            // physical
            temperature = (temperature_raw[0] - 273.15) * 1.8 + 32;
            for (size_t i = 0; i < 3; i++)
            {
                gyro[i] = (gyro_smooth[i] - gyro_bias[i]) * gyro_scale[i];
                accel[i] = (accel_smooth[i] - accel_bias[i]) * accel_scale[i];
            }

            // madgwick complemental filter
            madgwick_update();
        }
    }
}

void IMU_Module::madgwick_update()
{
}

void IMU_Module::gyro_static_calibr_task(void *pvParameters)
{
    TickType_t last_timestamp = 0;

    while (run_gyro_static_calibr)
    {
        if (timestamp != last_timestamp)
        {
            last_timestamp = timestamp;
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    // stop
}

void IMU_Module::gyro_z_scale_calibr_task(void *pvParameters)
{

    while (run_gyro_scale_calibr)
    {
        // calc gyro
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    // stop
}

void IMU_Module::aceel_sphere_calibr_task(void *pvParameters)
{

    while (run_accel_calibr)
    {
        // calc gyro
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    // stop
}
