#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"

class IMU_Module
{
private:
    float gyro_scale[3], gyro_scale_default[3];
    float gyro_bias[3];
    float accel_scale[3], accel_scale_default[3];
    float accel_bias[3];

    struct imu_sensor_interface interface; // 配置属性由模块实例来存放，底层驱动不可见

    IRAM_ATTR struct
    {
        char id[16] = "imu data";
        TickType_t timestamp;
        float gyro[3];
        float accel[3];
        float temperature;
        float quaternion[4];
        float euler_angle[3];
    } mem_imu_data = {0};

    /**
     * @brief main process of IMU data, send result to memory or message queue
     * @param pvParameters
     */
    void process_task(void *pvParameters);
    /**
     * @brief convert quaternion to euler
     * @param pvParameters
     * @note cost a lot of CPU
     */
    void convert_task(void *pvParameters);
    /**
     * @brief make imu fits to physic model
     * @param pvParameters
     */
    void calibrate_task(void *pvParameters);

public:
    IMU_Module(struct imu_sensor_interface &itf);
    ~IMU_Module();

    /**
     * @brief Get status of IMU
     */
    float get_gyro_x();
    float get_gyro_y();
    float get_gyro_z();
    float get_accel_x();
    float get_accel_y();
    float get_accel_z();
    float get_euler_roll();
    float get_euler_pitch();
    float get_euler_yaw();

    // float get_attitude(float);
};
