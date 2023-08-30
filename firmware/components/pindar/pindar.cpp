#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"

#include "pindar.h"
#include "pindar_config.h"

Pindar::Pindar()
{
	uart1 = new UART(PINDAR_UART_1_ID, PINDAR_UART_1_TX_IO_NUM, PINDAR_UART_1_RX_IO_NUM, 115200,1024,1024);
	uart1 = new UART(PINDAR_UART_1_ID, PINDAR_UART_1_TX_IO_NUM, PINDAR_UART_1_RX_IO_NUM, 115200,1024,1024);

	i2c_bus = new I2C_Bus(PINDAR_I2C_ID,PINDAR_I2C_SCK_IO_NUM,PINDAR_I2C_SDA_IO_NUM,PINDAR_I2C_BAUDRATE);
	spi2_bus = new SPI_Bus(PINDAR_IMU_SPI_ID, PINDAR_IMU_SPI_CS_IO_NUM, PINDAR_IMU_SPI_SCK_IO_NUM, PINDAR_IMU_SPI_MOSI_IO_NUM, PINDAR_IMU_SPI_MISO_IO_NUM, PINDAR_IMU_SPI_MODE, PINDAR_IMU_SPI_BAUDRATE);
	gpio_imu = new GPIO_Interrupt(PINDAR_GPIO_IMU);
	spi3_bus = new SPI_Bus(PINDAR_SPI_ID, PINDAR_SPI_CS_IO_NUM, PINDAR_SPI_SCK_IO_NUM, PINDAR_SPI_MOSI_IO_NUM, PINDAR_SPI_MISO_IO_NUM, PINDAR_SPI_MODE, PINDAR_SPI_BAUDRATE);

	gpio_1 = new GPIO_Normal(PINDAR_GPIO_1);
	gpio_2 = new GPIO_Normal(PINDAR_GPIO_2);
	gpio_3 = new GPIO_Normal(PINDAR_GPIO_3);
	gpio_4 = new GPIO_Normal(PINDAR_GPIO_4);
	gpio_5 = new GPIO_Normal(PINDAR_GPIO_5);
	gpio_6 = new GPIO_Normal(PINDAR_GPIO_6);
	gpio_7 = new GPIO_Normal(PINDAR_GPIO_7);
	gpio_8 = new GPIO_Normal(PINDAR_GPIO_8);
	gpio_9 = new GPIO_Normal(PINDAR_GPIO_9);
	gpio_10 = new GPIO_Normal(PINDAR_GPIO_10);
	gpio_11 = new GPIO_Normal(PINDAR_GPIO_11);
	gpio_12 = new GPIO_Normal(PINDAR_GPIO_12);
}

Pindar::~Pindar()
{
}
