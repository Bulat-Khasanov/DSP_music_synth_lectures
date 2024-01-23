#include "measure_time.h"

uint64_t startTimeCount(gptimer_handle_t *GPTimer_handler)
{
    uint64_t startCounter = 0;
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 10 * 1000 * 1000, // 10MHz, 1 tick = 0.1us
    };

    gptimer_new_timer(&timer_config, GPTimer_handler);
    gptimer_enable(*GPTimer_handler);
    gptimer_start(*GPTimer_handler);
    gptimer_get_raw_count(*GPTimer_handler, &startCounter);

    return startCounter;
}

uint64_t endTimeCount(gptimer_handle_t *GPTimer_handler)
{
    uint64_t endCounter = 0;

    gptimer_get_raw_count(*GPTimer_handler, &endCounter);
    gptimer_stop(*GPTimer_handler);
    gptimer_disable(*GPTimer_handler);
    gptimer_del_timer(*GPTimer_handler);

    return endCounter;
}