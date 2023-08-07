#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "string.h"

#include "imu_sensor_interface.h"
#include "icm42688.h"

extern "C" void app_main(void)
{

    struct imu_sensor_interface interface = {
        .init = icm42688_init,
        .deinit = nullptr,
        .read = icm42688_read,
        .gyro_full_scale_dps = 1000,
        .accel_full_scale_g = 16,
        .output_data_rate = 2000,
        .frame_intr_io_num = 21,
        .frame_event = xSemaphoreCreateBinary(),
    };

    icm42688_init(&interface);

    //     IMU_Module imu(interface);
}
