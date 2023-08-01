#include once

int pindar_init();
int pindar_deinit();

struct pindar_uart
{
    int tx_io_num;
    int rx_io_num;
    int id;
    int baud_rate;
    int tx_buffer_sz;
    int rx_buffer_sz;

    int data_bits;
    int stop_bits;
    int parity;
    int flow_control;
};
int pindar_uart_open(struct pindar_uart *uart);
int pindar_uart_read(struct pindar_uart *uart, char *data, int len);
int pindar_uart_write(struct pindar_uart *uart, char *data, int len);
int pindar_uart_flush(struct pindar_uart *uart);
int pindar_uart_close(struct pindar_uart *uart);

struct pindar_i2c
{
    int tx_io_num;
    int rx_io_num;
    int id;
    int address;
};

int pindar_i2c_read();
int pindar_i2c_write();