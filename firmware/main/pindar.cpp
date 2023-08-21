
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include "pindar.h"
#include "pindar_config.h"

Pindar::Pindar()
{
    spi2_handle = new SPI_Interface(PINDAR_IMU_SPI_ID, PINDAR_IMU_SPI_CS_IO_NUM, PINDAR_IMU_SPI_SCK_IO_NUM, PINDAR_IMU_SPI_MOSI_IO_NUM, PINDAR_IMU_SPI_MISO_IO_NUM, PINDAR_IMU_SPI_MODE, PINDAR_IMU_SPI_BAUDRATE);
    // gpio_intr_imu = new GPIOInterrupt(PINDAR_GPIO_IMU);
    spi3_handle = new SPI_Interface(PINDAR_SPI_ID, PINDAR_SPI_CS_IO_NUM, PINDAR_SPI_SCK_IO_NUM, PINDAR_SPI_MOSI_IO_NUM, PINDAR_SPI_MISO_IO_NUM, PINDAR_SPI_MODE, PINDAR_SPI_BAUDRATE);
}

Pindar::~Pindar()
{
}

void gpio_isr_handler(void *arg)
{
    //     ((struct gpio_intr_interface *)arg)->timestamp = xTaskGetTickCountFromISR();

    //     BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    //     xSemaphoreGiveFromISR(((struct gpio_intr_interface *)arg)->event, &xHigherPriorityTaskWoken);
}
