#include "signal_gen.h"
#include "unity.h"
#include <stdio.h>
#include "driver/gptimer.h"

#define SEVERAL_TIMES 12

#define TEN_TIMES_MY_FUNCTION_TIME 10*30

static uint64_t startTimeCount(gptimer_handle_t *GPTimer_handler);
static uint64_t endTimeCount(gptimer_handle_t *GPTimer_handler);
static void getSignalExample(uint8_t arr[]);

static char msg[256] = {0};

static uint64_t startTimeCount(gptimer_handle_t *GPTimer_handler)
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

static uint64_t endTimeCount(gptimer_handle_t *GPTimer_handler)
{
    uint64_t endCounter = 0;

    gptimer_get_raw_count(*GPTimer_handler, &endCounter);
    gptimer_stop(*GPTimer_handler);
    gptimer_disable(*GPTimer_handler);
    gptimer_del_timer(*GPTimer_handler);

    return endCounter;
}

static void getSignalExample(uint8_t arr[])
{
    uint32_t i;

    for (i = 0; i < DAC_RESOLUTION; i++)
    {
        arr[i] = getOneElementOfSignal();
    }
}

void setUp(void)
{

}

void tearDown(void)
{

}

void test_isSignalRepeats(void)
{
    uint8_t readSig[DAC_RESOLUTION];
    uint32_t sigArrElNum = 0;

    getSignalExample(readSig);

    for (sigArrElNum = 0; sigArrElNum < DAC_RESOLUTION; sigArrElNum++)
    {
        uint8_t currSigEl = getOneElementOfSignal();
        sprintf(msg, "Test fails on %ld array element", sigArrElNum);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(readSig[sigArrElNum], currSigEl, msg); 
    }
}

void test_isSignalRepeatsSeveralTimes(void)
{
    uint8_t readSig[DAC_RESOLUTION];
    uint32_t sigArrElNum = 0;
    uint32_t periodNum = 0;

    getSignalExample(readSig);

    for (periodNum = 0; periodNum < SEVERAL_TIMES; periodNum++)
    {
        for (sigArrElNum = 0; sigArrElNum < DAC_RESOLUTION; sigArrElNum++)
        {
            uint8_t currSigEl = getOneElementOfSignal();
            sprintf(msg, "Test fails on %ld array element and %ld period", sigArrElNum, periodNum);
            TEST_ASSERT_EQUAL_UINT8_MESSAGE(readSig[sigArrElNum], currSigEl, msg); 
        }
    }
}

void test_isFunctionComputingTimeToleratable(void)
{
    gptimer_handle_t gptimer = NULL;
    uint64_t start, end;
    clock_t toleratableTime = TEN_TIMES_MY_FUNCTION_TIME;
    clock_t realTime = 0;

    start = startTimeCount(&gptimer);
    getOneElementOfSignal();
    end = endTimeCount(&gptimer);
    realTime = end - start;

    sprintf(msg, "Function computing time is not toleratable, it's greater than %ld", toleratableTime);
    TEST_ASSERT_LESS_THAN_MESSAGE(toleratableTime, realTime, msg);
}

void app_main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_isFunctionComputingTimeToleratable);
    RUN_TEST(test_isSignalRepeats);
    RUN_TEST(test_isSignalRepeatsSeveralTimes);

    UNITY_END();
}