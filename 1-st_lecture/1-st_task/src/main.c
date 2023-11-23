#include "main.h"

static void appInit(void)
{
    #if DEBUG
    debugLedInit();
    uartInit();
    #endif
}

void app_main() 
{
    appInit();

}

