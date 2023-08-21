
// #pragma once

// #include <stdint.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/semphr.h"

// class IMU_Interface // 纯接口类
// {
// public:
//     virtual ~IMU_Interface() {} // 确保能调用派生类的析构

//     virtual int initialize() = 0;
//     virtual int read_raw_data(int16_t *gyro, int16_t *accel, int16_t *temperature) = 0;
//     virtual int set_data_rate(int data_rate) = 0;
//     virtual int set_gyro_full_scale(int gyro_full_scale) = 0;
//     virtual int set_accel_full_scale(int accel_full_scale) = 0;

//     QueueHandle_t frame_event;

// };



// class IMU_Module
// {
// public:
//     IMU_Module(IMU_Interface *imu_interface) : interface(imu_interface) {}

//     bool initialize()
//     {
//         return interface->initialize();

//         // xtaskcreate(scan_task, "scan_task", 4096, NULL, 5, NULL);
//     }


//     // 添加其他计算、校准等方法
//     // 例如：计算姿态角、进行校准等

// private:
//     IMU_Interface *interface;

// };



// // int main()
// // {
// //     ConcreteSPI spi;            // 具体的 SPI 接口实例
// //     ICM42688IMU icm42688(&spi); // ICM42688IMU 实例

// //     IMU_Module imuModule(&icm42688); // IMU_Module 实例

// //     imuModule.initialize();
// //     float accelX, accelY, accelZ;
// //     imuModule.readAccelerometer(accelX, accelY, accelZ);

// //     // 进行其他计算、校准等操作
// //     // 例如：计算姿态角、进行校准等

// //     return 0;
// // }