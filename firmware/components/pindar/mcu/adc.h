#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

class ADC_Once {
private:
    adc_oneshot_unit_handle_t adc1_handle = NULL;
            adc_cali_handle_t adc1_cali_handle = NULL;

public:
    ADC_Once(adc_unit_t id, adc_channel_t *channel, uint8_t num){
        
        adc_oneshot_unit_init_cfg_t init_config1 = {
            .unit_id = ADC_UNIT_1,
            .ulp_mode = ADC_ULP_MODE_DISABLE,
        };
        adc_oneshot_new_unit(&init_config1, &adc1_handle));

        adc_oneshot_chan_cfg_t config = {
            .bitwidth = ADC_BITWIDTH_DEFAULT,
            .atten = ADC_ATTEN_DB_11,
        };

        for () {

            adc_oneshot_config_channel(adc1_handle, channel[i], &config));

            int  voltage;
            adc_oneshot_read(adc1_handle, channel[i], &adc_raw);

            adc_cali_line_fitting_config_t cali_config = {
                .unit_id = unit,
                .atten = atten,
                .bitwidth = ADC_BITWIDTH_DEFAULT,
            };
            ret = adc_cali_create_scheme_line_fitting(&cali_config, &adc1_cali_handle);
            if (ret == ESP_OK) {
                calibrated = true;

                adc_cali_raw_to_voltage(adc1_cali_handle, adc_raw, &voltage);

            }
        }
    };

    ~ADC_Once(){

        adc_oneshot_del_unit(adc1_handle);
        if(adc1_cali_handle){

            adc_cali_delete_scheme_line_fitting(adc1_cali_handle));
        }
        ESP_LOGI(TAG, "deregister %s calibration scheme", "Line Fitting");
    }

    int get(adc_channel_t channel){
        
        int adc_raw;
        
        adc_oneshot_read(adc1_handle, channel, &adc_raw);

        return adc_raw;
    };

};

class ADC_DMA {
private:
    int adc_raw[10];

public:
    ADC_DMA(channel, pin, ){


    
    };

};