#include "signal_gen.h"

uint8_t getOneElementOfSignal(void)
{
    static uint8_t indx;

    return signal[indx++];
}