#pragma once

#define PINDAR_FW_VERSION "1.0.0"
#define PINDAR_HW_VERSION "1.0.0"
#define PINDAR_API_VERSION "1.0.0"

#define PINDAR_ADC_1_IO_NUM 0
#define PINDAR_ADC_2_IO_NUM 1
#define PINDAR_ADC_3_IO_NUM 2
#define PINDAR_ADC_4_IO_NUM 3

#define PINDAR_UART_1_ID 0
#define PINDAR_UART_1_TX_IO_NUM 0
#define PINDAR_UART_1_RX_IO_NUM 1

#define PINDAR_UART_2_ID 0
#define PINDAR_UART_2_TX_IO_NUM 0
#define PINDAR_UART_2_RX_IO_NUM 1

#define PINDAR_I2C_ID 0
#define PINDAR_I2C_SCK_IO_NUM 0
#define PINDAR_I2C_SDA_IO_NUM 1

#define PINDAR_IMU_SPI_ID SPI2_HOST
#define PINDAR_IMU_SPI_CS_IO_NUM GPIO_NUM_14
#define PINDAR_IMU_SPI_SCK_IO_NUM GPIO_NUM_13
#define PINDAR_IMU_SPI_MOSI_IO_NUM GPIO_NUM_12
#define PINDAR_IMU_SPI_MISO_IO_NUM GPIO_NUM_11
#define PINDAR_IMU_SPI_MODE 0
#define PINDAR_IMU_SPI_BAUDRATE (10 * 1000000)

#define PINDAR_SPI_ID SPI3_HOST
#define PINDAR_SPI_CS_IO_NUM GPIO_NUM_3
#define PINDAR_SPI_SCK_IO_NUM GPIO_NUM_46
#define PINDAR_SPI_MOSI_IO_NUM GPIO_NUM_9
#define PINDAR_SPI_MISO_IO_NUM GPIO_NUM_10
#define PINDAR_SPI_MODE 0
#define PINDAR_SPI_BAUDRATE (10 * 1000000)

#define PINDAR_GPIO_IMU GPIO_NUM_21
#define PINDAR_GPIO_1 GPIO_NUM_0
#define PINDAR_GPIO_2 GPIO_NUM_1
#define PINDAR_GPIO_3 GPIO_NUM_2
#define PINDAR_GPIO_4 GPIO_NUM_3
#define PINDAR_GPIO_5 GPIO_NUM_4
#define PINDAR_GPIO_6 GPIO_NUM_5
#define PINDAR_GPIO_7 GPIO_NUM_6
#define PINDAR_GPIO_8 GPIO_NUM_7
#define PINDAR_GPIO_9 GPIO_NUM_8
#define PINDAR_GPIO_10 GPIO_NUM_9
#define PINDAR_GPIO_11 GPIO_NUM_10
#define PINDAR_GPIO_12 GPIO_NUM_11

#define CALLBACK_LAMBDA_VOID(_CLASS, _MEMBER) \
    [](void *_func) { static_cast<_CLASS *>(_func)->_MEMBER(_func); }
