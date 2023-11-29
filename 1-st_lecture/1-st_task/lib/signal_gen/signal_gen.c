#include "signal_gen.h"

static uint8_t indx = 0;

uint8_t getOneElementOfSignal(void)
{
    return signal[indx++];
}