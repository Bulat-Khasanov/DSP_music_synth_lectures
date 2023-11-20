#include "debug_led.h"
#include "debug_uart.h"
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

