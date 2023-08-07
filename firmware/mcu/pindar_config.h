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

#define PINDAR_SPI_ID 0
#define PINDAR_SPI_CS_IO_NUM 0
#define PINDAR_SPI_SCK_IO_NUM 3
#define PINDAR_SPI_MOSI_IO_NUM 1
#define PINDAR_SPI_MISO_IO_NUM 2

#define PINDAR_GPIO_1 0
#define PINDAR_GPIO_2 1
#define PINDAR_GPIO_3 2
#define PINDAR_GPIO_4 3
#define PINDAR_GPIO_5 4
#define PINDAR_GPIO_6 5
#define PINDAR_GPIO_7 6
#define PINDAR_GPIO_8 7
#define PINDAR_GPIO_9 8
#define PINDAR_GPIO_10 9
#define PINDAR_GPIO_11 10
#define PINDAR_GPIO_12 11

enum IMU_Sensor
{
    NONE,
    ICM42688,
    BMI088,
    ST
};
#define PINDAR_IMU_SENSOR ICM42688