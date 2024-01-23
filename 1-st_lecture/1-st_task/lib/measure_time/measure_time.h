/**
 * This module allows measuring time during certain actions. This way, 
 * one can measure how long it takes to execute, for example, a function.
*/
#include "driver/gptimer.h"

/**
 * @brief The function configures and starts a timer with a frequency of 10 MHz.
 * @param GPTimer_handler Timer handler.
 * @return The number of timer counts that have elapsed since the timer was started.
*/
extern uint64_t startTimeCount(gptimer_handle_t *GPTimer_handler);

/**
 * @brief The function retrieves the timer value, then turns off and 
 *        deconfigures the timer.
 * @param GPTimer_handler Timer handler.
 * @return The number of timer counts that have elapsed since the timer was started.
*/
extern uint64_t endTimeCount(gptimer_handle_t *GPTimer_handler);