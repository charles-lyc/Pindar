/**
 * @file icm42688.c
 * @brief 暂时只支持单个实例器件，等挂俩再把icm_handler抽象出来就行了。
 * @author chaoz (charles-lyc@outlook.com)
 * @version 0.1
 * @date 2023-08-06
 */

#include <stdio.h>
#include "string.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

#include "imu_sensor_interface.h"

static const char *TAG = "icm42688";

#define DEVICE_CONFIG 0x11
#define INT_CONFIG 0x14
#define FIFO_CONFIG 0x16
#define TEMP_DATA1 0x1D
#define TEMP_DATA0 0x1E
#define INT_STATUS 0x2D
#define FIFO_COUNTH 0x2E
#define FIFO_COUNTL 0x2F
#define FIFO_DATA 0x30
#define SIGNAL_PATH_RESET 0x4B
#define INTF_CONFIG0 0x4C
#define INTF_CONFIG1 0x4D
#define PWR_MGMT0 0x4E
#define GYRO_CONFIG0 0x4F
#define ACCEL_CONFIG0 0x50
#define GYRO_CONFIG1 0x51
#define GYRO_ACCEL_CONFIG0 0x52
#define ACCEL_CONFIG1 0x53
#define FIFO_CONFIG1 0x5F
#define FIFO_CONFIG2 0x60
#define FIFO_CONFIG3 0x61
#define INT_CONFIG0 0x63
#define INT_SOURCE0 0x65
#define SELF_TEST_CONFIG 0x70
#define WHO_AM_I 0x75
#define REG_BANK_SEL 0x76
#define DELAY_MS 0xFF

uint8_t reg_table[] = {
    SIGNAL_PATH_RESET, 0x01 << 3,
    PWR_MGMT0, 0x03 << 2 | 0x03,
    DELAY_MS, 100,
    GYRO_CONFIG0, 0x02 << 5 | 0x06,  // 500 dps, odr: 1kHz
    ACCEL_CONFIG0, 0x02 << 5 | 0x06, // acc: 4g, odr: 1kHz
    //{GYRO_CONFIG1, 0},			// TODO: re setup
    //{GYRO_ACCEL_CONFIG0, 0},
    //{ACCEL_CONFIG1}
};

static int set_output_data_rate(int rate)
{
    return 0;
}

static int set_full_scale(int gyro_full_scale_dps, int accel_full_scale_g)
{
    return 0;
}

static void gpio_isr_handler(void *arg)
{
    ((struct imu_sensor_interface *)arg)->timestamp = xTaskGetTickCountFromISR();

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(((struct imu_sensor_interface *)arg)->frame_event, &xHigherPriorityTaskWoken);
}

static int spi_read(uint8_t addr, uint8_t *data, int len)
{
    return 0;
}

static int spi_write(uint8_t addr, uint8_t *data, int len)
{
    return 0;
}

int icm42688_init(struct imu_sensor_interface *interface)
{
    uint8_t value = 0;
    spi_device_handle_t handle;
    spi_bus_config_t buscfg = {
        .miso_io_num = 11,
        .mosi_io_num = 12,
        .sclk_io_num = 13,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 64,
    };
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 200000,
        .mode = 0,
        .spics_io_num = 14,
        .queue_size = 64,
    };

    // init bus
    if (spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO) != ESP_OK)
    {
        ESP_LOGE(TAG, "spi_bus_initialize failed");
        goto fail;
    }
    if (spi_bus_add_device(SPI2_HOST, &devcfg, &handle) != ESP_OK)
    {
        ESP_LOGE(TAG, "spi_bus_add_device failed");
        goto fail;
    }

    // check if sensor exist
    spi_read(WHO_AM_I, &value, 1);
    if (value != 0x47)
    {
        ESP_LOGE(TAG, "sensor not found");
        goto fail;
    }

    // config sensor registers
    uint8_t *p_table;
    p_table = reg_table;
    for (int i = 0; i < sizeof(reg_table) / 2; i++)
    {
        spi_write(*p_table, p_table + 1, 1);
        p_table += 2;
        vTaskDelay(1 / portTICK_PERIOD_MS);

        if (*p_table == DELAY_MS)
        {
            vTaskDelay((*(p_table + 1)) / portTICK_PERIOD_MS);
            p_table += 2;
        }
    }
    p_table = reg_table;
    for (int i = 0; i < sizeof(reg_table) / 2; i++)
    {
        spi_read(*p_table, &value, 1);
        if (value != *(p_table + 1))
        {
            ESP_LOGE(TAG, "sensor register mismatch");
            goto fail;
        }
        p_table += 2;
        vTaskDelay(1 / portTICK_PERIOD_MS);

        if (*p_table == DELAY_MS)
        {
            p_table += 2;
        }
    }

    // customize
    if (set_output_data_rate(interface->output_data_rate))
    {
        ESP_LOGE(TAG, "set_output_data_rate failed");
        goto fail;
    }
    if (set_full_scale(interface->gyro_full_scale_dps, interface->accel_full_scale_g))
    {
        ESP_LOGE(TAG, "set_full_scale failed");
        goto fail;
    }

    // config gpio interrupt
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_POSEDGE,
        .pin_bit_mask = (1ULL << interface->frame_intr_io_num),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&io_conf);
    gpio_set_intr_type(interface->frame_intr_io_num, GPIO_INTR_POSEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
    gpio_isr_handler_add(interface->frame_intr_io_num, gpio_isr_handler, interface->frame_event);

    return 0;
fail:
    ESP_LOGE("IMU_MODULE_TAG", "init failed");
    return -1;
}

int icm42688_read(struct imu_sensor_interface *interface, TickType_t *timestamp, int32_t *gyro, int32_t *accel, int32_t *temp)
{
    int16_t buffer[20] = {0};

    *timestamp = interface->timestamp;

    spi_read(TEMP_DATA0, (uint8_t *)buffer, 14);

    temp[0] = buffer[0];
    gyro[0] = buffer[1];
    gyro[0] = buffer[1];
    gyro[0] = buffer[1];
    accel[0] = buffer[1];
    accel[0] = buffer[1];
    accel[0] = buffer[1];

    return 0;
}

void icm42688_resolution_LSB(float *gyro, float *accel)
{
}
