#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mcu/uart.h"
class Serial
{
private:
    UART *uart_handle;

public:
    Serial::Serial(UART *uart, int baudrate)
    {
        uart_handle = uart;
        uart_handle.set_baudrate(baudrate);
    }

    Serial::~Serial()
    {
    }

    int read(void *src, size_t size, TickType_t ticks_to_wait = portMAX_DELAY)
    {
        return uart_handle->read( src, size, ticks_to_wait);
    };

    int write(const void *src, size_t size)
    {
        return uart_handle->write( src, size);
    };
};


