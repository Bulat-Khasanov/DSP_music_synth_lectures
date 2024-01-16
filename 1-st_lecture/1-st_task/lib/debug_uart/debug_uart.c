#include "debug_uart.h"

#include "driver/uart.h"
#include "hal/gpio_types.h"
#include <string.h>

/* Private macros. Only modify if you know what you're doing. */
#define UART_BUFF_SIZE 128
#define UART_NUM UART_NUM_2

void uartInit(void)
{    
    /* Set platformIO defalut values. */
    uart_config_t uart_config = {
        .baud_rate = 9600, 
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    /* Install UART driver, and get the queue. */
    uart_driver_install(UART_NUM, UART_BUFF_SIZE*2, 0, 0, NULL, 0);
    
    /* Configure UART parameters. */
    uart_param_config(UART_NUM, &uart_config);

    /* Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19) */
    uart_set_pin(UART_NUM, GPIO_NUM_17, GPIO_NUM_16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void uart2Print(char str[])
{
    uart_write_bytes(UART_NUM, str, strlen(str));
}