
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef USE_NVS_SET
template <typename T>
class ParameterManager
{
private:
    const char *paramName;
    nvs_handle_t my_handle;

public:
    ParameterManager(const char *paramName) : paramName(paramName)
    {
        // Initialize NVS
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);

        // Open
        ret = nvs_open("storage", NVS_READWRITE, &my_handle);
        ESP_ERROR_CHECK(ret);
    }

    T operator=(T value)
    {
        esp_err_t ret = nvs_set(my_handle, paramName, value);
        ESP_ERROR_CHECK(ret);
        // Commit
        ret = nvs_commit(my_handle);
        ESP_ERROR_CHECK(ret);
        return value;
    }

    operator T()
    {
        T value;
        esp_err_t ret = nvs_get(my_handle, paramName, &value);
        switch (ret)
        {
        case ESP_OK:
            printf("Parameter %s exists\n", paramName);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("Parameter %s does not exist\n", paramName);
            break;
        default:
            printf("Error (%s) reading!\n", esp_err_to_name(ret));
        }
        return value;
    }

    ~ParameterManager()
    {
        // Close
        nvs_close(my_handle);
    }
};

ParameterManager<int32_t> intManager("intParam");
ParameterManager<bool> boolManager("boolParam");
ParameterManager<float> floatManager("floatParam");

#else

class ParameterManagerBase
{
protected:
    const char *paramName;
    nvs_handle_t my_handle;
    bool cached = false;

public:
    ParameterManagerBase(const char *paramName) : paramName(paramName)
    {
        // Initialize NVS
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);

        // Open
        ret = nvs_open("storage", NVS_READWRITE, &my_handle);
        ESP_ERROR_CHECK(ret);
    }

    ~ParameterManagerBase()
    {
        // Close
        nvs_close(my_handle);
    }
};

class Param_Int32 : public ParameterManagerBase
{
private:
    int32_t value_temp;

public:
    Param_Int32(const char *paramName) : ParameterManagerBase(paramName) {}

    int32_t operator=(int32_t value)
    {
        esp_err_t ret = nvs_set_i32(my_handle, paramName, value);
        ESP_ERROR_CHECK(ret);
        // Commit
        ret = nvs_commit(my_handle);
        ESP_ERROR_CHECK(ret);
        cached = false;
        return value;
    }

    operator int32_t()
    {
        if (cached)
            return value_temp;

        int32_t value;
        esp_err_t ret = nvs_get_i32(my_handle, paramName, &value);
        ESP_ERROR_CHECK(ret);
        value_temp = value;
        cached = true;
        return value;
    }
};

class Param_Bool : public ParameterManagerBase
{
private:
    bool value_temp;

public:
    Param_Bool(const char *paramName) : ParameterManagerBase(paramName) {}

    bool operator=(bool value)
    {
        esp_err_t ret = nvs_set_u8(my_handle, paramName, value ? 1 : 0);
        ESP_ERROR_CHECK(ret);
        // Commit
        ret = nvs_commit(my_handle);
        ESP_ERROR_CHECK(ret);
        cached = false;
        return value;
    }

    operator bool()
    {
        if (cached)
            return value_temp;

        uint8_t value;
        esp_err_t ret = nvs_get_u8(my_handle, paramName, &value);
        ESP_ERROR_CHECK(ret);
        value_temp = (value != 0);
        cached = true;
        return value != 0;
    }
};

class Param_Float : public ParameterManagerBase
{
private:
    float value_temp;

public:
    Param_Float(const char *paramName) : ParameterManagerBase(paramName) {}

    float operator=(float value)
    {
        esp_err_t ret = nvs_set_blob(my_handle, paramName, &value, sizeof(float));
        ESP_ERROR_CHECK(ret);
        // Commit
        ret = nvs_commit(my_handle);
        ESP_ERROR_CHECK(ret);
        cached = false;
        return value;
    }

    operator float()
    {
        if (cached)
            return value_temp;

        float value;
        esp_err_t ret = nvs_get_blob(my_handle, paramName, &value, nullptr);
        ESP_ERROR_CHECK(ret);
        value_temp = value;
        cached = true;
        return value;
    }
};

class Param_String : public ParameterManagerBase
{
private:
    std::string value_temp;

public:
    Param_String(const char *paramName) : ParameterManagerBase(paramName) {}

    std::string operator=(const std::string &value)
    {
        esp_err_t ret = nvs_set_str(my_handle, paramName, value.c_str());
        ESP_ERROR_CHECK(ret);
        // Commit
        ret = nvs_commit(my_handle);
        ESP_ERROR_CHECK(ret);
        cached = false;
        return value;
    }

    operator std::string()
    {
        if (cached)
            return value_temp;

        size_t required_size;
        esp_err_t ret = nvs_get_str(my_handle, paramName, nullptr, &required_size);
        ESP_ERROR_CHECK(ret);
        char *value = new char[required_size];
        ret = nvs_get_str(my_handle, paramName, value, &required_size);
        ESP_ERROR_CHECK(ret);
        std::string str_value(value);
        delete[] value;
        value_temp = str_value;
        cached = true;
        return str_value;
    }
};

#endif