#ifndef DUEBUG_UART_H
#define DUEBUG_UART_H
/**
 * Debugging module using UART. Allows the device to transmit data using the UART port. 
 * The module uses UART2, with GPIO17 as TX and GPIO16 as RX. No other pins are 
 * required for data transmission.
*/

/** 
 * @brief Initializes the UART2. TX: GPIO17, RX: GPIO16.
 * @note The function must be executed before using other functions/macros from 
 *       this component.
 */
void uartInit(void);

/**
 * @brief Outputs the string passed to the function.
 * @warning The string must end with character '\0'
 * @param str String that will be output to UART.
*/
void uart2Print(char str[]);

#endif /* debug_uart.h */
