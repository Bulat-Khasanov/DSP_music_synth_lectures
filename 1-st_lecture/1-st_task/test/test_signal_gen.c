#include "signal_gen.h"
#include "unity.h"
#include <stdio.h>
#include "soc/clk_tree_defs.h"

#define SEVERAL_TIMES 12

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

void TC0_isSignalRepeats(void)
{
    uint8_t readSig[DAC_RESOLUTION];
    uint32_t sigArrElNum = 0;

    getSignalExample(readSig);

    for (sigArrElNum = 0; sigArrElNum < DAC_RESOLUTION; sigArrElNum++)
    {
        char msg[256] = {};
        uint8_t currSigEl = getOneElementOfSignal();
        sprintf(msg, "Test fails on %ld array element", sigArrElNum);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(readSig[sigArrElNum], currSigEl, msg); 
    }
}

void TC1_isSignalRepeatsSeveralTimes(void)
{
    uint8_t readSig[DAC_RESOLUTION];
    uint32_t sigArrElNum = 0;
    uint32_t periodNum = 0;

    getSignalExample(readSig);

    for (periodNum = 0; periodNum < SEVERAL_TIMES; periodNum++)
    {
        for (sigArrElNum = 0; sigArrElNum < DAC_RESOLUTION; sigArrElNum++)
        {
            char msg[256] = {};
            uint8_t currSigEl = getOneElementOfSignal();
            sprintf(msg, "Test fails on %ld array element and %ld period", sigArrElNum, periodNum);
            TEST_ASSERT_EQUAL_UINT8_MESSAGE(readSig[sigArrElNum], currSigEl, msg); 
        }
    }
}

void TC2_isFunctionComputingTimeToleratable(void)
{
    clock_t start, end;
    clock_t toleratableTime = 1;
    clock_t realTime = 0;
    char msg[256];

    start = clock();
    getOneElementOfSignal();
    end = clock()+1;
    realTime = end - start;

    sprintf(msg, "Function computing time is not toleratable, it's greater than %ld", toleratableTime);
    TEST_ASSERT_LESS_THAN_MESSAGE(toleratableTime, realTime, msg);
}

void app_main(void)
{
    UNITY_BEGIN();

    RUN_TEST(TC0_isSignalRepeats);
    RUN_TEST(TC1_isSignalRepeatsSeveralTimes);
    RUN_TEST(TC2_isFunctionComputingTimeToleratable);

    UNITY_END();
}