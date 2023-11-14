#ifndef DUEBUG_LED_H
#define DUEBUG_LED_H
/**
 * The simplest debugging tool that allows you to transmit 1 bit of information 
 * (for example, to check the setting/unsetting of a specific register, 
 * passing/skipping a branch).
 */

/** 
 * This macro defines which pin the built-in LED on the debug board is located on.
 * Change only if your board is different from those listed in platformio.ini. 
 */
#define LED_GPIO GPIO_NUM_2

/** 
 * @brief Initializes the LED located on the board. 
 * @note The function must be executed before using other functions/macros from 
 *       this component.
 */
void debugLedInit(void);

/**
 * @brief Turns on the debug LED. 
 */
void debugLedSet(void);

/**
 * @brief Checks if one value matches another. If the values are equal, it lights 
 *        up the debug LED.
 * @param output   The value you are planning to check.
 * @param expected Expected value.
 */
#define LED_ASSERT(output, expected) \
do {                                 \
    if ((output) == (expected))      \
    {                                \
        debugLedSet();               \
    }                                \
} while (0)                          \

#endif