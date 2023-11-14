#include "debug_led.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"

void debugLedInit(void)
{
    gpio_config_t gpioConfig = {
        1 << LED_GPIO,
        GPIO_MODE_OUTPUT,
        GPIO_PULLUP_ENABLE,
        GPIO_PULLDOWN_DISABLE,
        GPIO_INTR_DISABLE
    };

    gpio_config(&gpioConfig);
}

void debugLedSet(void)
{
    gpio_set_level(LED_GPIO, 1);
}
