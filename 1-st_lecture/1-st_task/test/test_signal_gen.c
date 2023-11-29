#include "signal_gen.h"
#include <unity.h>

void setUp(void)
{

}

void tearDown(void)
{

}

void TC0_isSignalRepeats(void)
{
    uint8_t readSig[DAC_RESOLUTION] = {0};
    uint32_t sigArrElNum = 0;

    for (sigArrElNum = 0; sigArrElNum < DAC_RESOLUTION; sigArrElNum++)
    {
        readSig[sigArrElNum] = getOneElementOfSignal();
    }

    for (sigArrElNum = 0; sigArrElNum < DAC_RESOLUTION; sigArrElNum++)
    {
        uint8_t currSigEl = getOneElementOfSignal();
        TEST_ASSERT_EQUAL_UINT8(readSig[sigArrElNum], currSigEl); 
    }
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(TC0_isSignalRepeats);

    return UNITY_END();
}