
#include "pindar.h"

int pindar_uart_open(struct pindar_uart *uart)
{
    const uart_config_t uart_config = {
        .baud_rate = uart->baud_rate,
        .data_bits = UART_DATA_8_BITS,
        // default
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    int id = uart->id - 1;

    // We won't use a buffer for sending data.
    uart_driver_install(id, uart->rx_buffer_sz, uart->tx_buffer_sz, 0, NULL, 0);
    uart_param_config(id, &uart_config);
    uart_set_pin(id, uart->tx_io_num, uart->rx_io_num, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    return 0;
}

int pindar_uart_read(struct pindar_uart *uart, char *data, int len)
{
    return 0;
}

int pindar_uart_write(struct pindar_uart *uart, char *data, int len)
{
    return 0;
}

int pindar_uart_flush(struct pindar_uart *uart)
{
    return 0;
}

int pindar_uart_close(struct pindar_uart *uart)
{
    return 0;
}

