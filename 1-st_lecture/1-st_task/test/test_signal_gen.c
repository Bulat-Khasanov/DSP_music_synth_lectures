#include "signal_gen.h"
#include "unity.h"
#include <stdio.h>
#include "esp_cpu.h"

/* A value representing a certain number of test runs of the signal. */
#define SEVERAL_TIMES 12

/**
 * The macro contains the number of processor cycles required to process the 
 * simplest target function in C.
*/
#define OPTIMAL_TIME 1934

/* The function fills the passed array with the signal. */
static void getSignalExample(uint8_t arr[]);

/* A line in which messages about failed asserts are output during the execution of tests. */
static char msg[256] = {0};

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

/* The test checks the repeatability of the signal. */
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

/* The test checks the repeatability of the signal several times. */
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

/* The test checks whether the target function takes too long to execute. */
void test_isFunctionComputingTimeToleratable(void)
{
    esp_cpu_cycle_count_t start, end;
    esp_cpu_cycle_count_t toleratableTime = 3 * OPTIMAL_TIME; 
    esp_cpu_cycle_count_t realTime = 0;

    start = esp_cpu_get_cycle_count();
    getOneElementOfSignal();
    end = esp_cpu_get_cycle_count();
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