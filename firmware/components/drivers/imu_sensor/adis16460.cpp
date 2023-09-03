/**
 * @file icm42688.c
 * @brief 暂时只支持单个实例器件，等挂俩再把icm_handler抽象出来就行了。
 * @author chaoz (charles-lyc@outlook.com)
 * @version 0.1
 * @date 2023-08-06
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_log.h"
#include "esp_system.h"

#include "adis16460.h"
#include "pindar/mcu/bus.h"

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
#define FSYNC_CONFIG 0x64
#define INT_SOURCE0 0x65
#define SELF_TEST_CONFIG 0x70
#define WHO_AM_I 0x75
#define REG_BANK_SEL 0x76
#define DELAY_MS 0xFF

static uint8_t reg_table[] = {
};

ADIS16460::ADIS16460(Bus_Base *bushw)
{
	bus = bushw;

	// config spi bus mode, baudrate .etc

}

ADIS16460::~ADIS16460()
{
	bus = nullptr;
}

int ADIS16460::probe()
{
	uint8_t tx[2] = {0};
	uint8_t rx[2] = {0};

	// probe
	tx[0] = WHO_AM_I;
	bus->transfer(Bus_Base::Read, tx, 1, rx, 2);
	if (rx[1] != 0x47) {
		ESP_LOGE("ADIS16460", "probe fail");
		return -1;
	}

	return 0;
}

int ADIS16460::initialize()
{
	uint8_t tx[2] = {0};
	uint8_t rx[2] = {0};

	// power reset

	// config sensor registers
	uint8_t *p_table = reg_table;
	for (int i = 0; i < sizeof(reg_table) / 2; i++) {
		tx[0] = *p_table++;
		tx[1] = *p_table++;
		bus->transfer(Bus_Base::Write, tx, 2, rx, 2);
		vTaskDelay(1 / portTICK_PERIOD_MS);
	}
	// p_table = reg_table;
	// for (int i = 0; i < sizeof(reg_table) / 2; i++) {
	//  tx[0] = *p_table++;
	//  bus->transfer(Bus_Base::READ, tx, rx, 2);
	//  ESP_LOGI("ADIS16460", "rx %x %x", rx[ 0], rx[ 1]);
	//  if (rx[1] != *p_table++) {
	//      ESP_LOGE("ADIS16460", "config fail");
	//      // return -1;
	//  }
	// }

	ESP_LOGI("ADIS16460", "ready.");

	return 0;
}

int ADIS16460::read_raw_data(int32_t *gyro, int32_t *accel, int16_t *temp)
{
	uint8_t tx[14] = {0xFF};
	uint8_t rx[14] = {0};

	tx[0] = TEMP_DATA1;
	bus->transfer(Bus_Base::Read, tx, 1, rx, 14);

	temp[0] = (int16_t)rx[1] << 8 | rx[0];

	accel[0] = (int32_t)rx[3] << 8 | rx[2];
	accel[1] = (int32_t)rx[5] << 8 | rx[4];
	accel[2] = (int32_t)rx[7] << 8 | rx[6];
	gyro[0] = (int32_t)rx[9] << 8 | rx[8];
	gyro[1] = (int32_t)rx[11] << 8 | rx[10];
	gyro[2] = (int32_t)rx[13] << 8 | rx[12];

	return 0;
}

// void icm42688_resolution_LSB(float *gyro, float *accel)
// {
// }

// int set_output_data_rate(int rate)
// {
//     return 0;
// }

// int set_full_scale(int gyro_full_scale_dps, int accel_full_scale_g)
// {
//     return 0;
// }
