#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define PIR_GPIO 15
#define LED_RED_GPIO 14
#define LED_GREEN_GPIO 13
#define LED_BLUE_GPIO 12

void gpio_setup(void) {
    gpio_init(PIR_GPIO);
    gpio_set_dir(PIR_GPIO, GPIO_IN);

    gpio_init(LED_RED_GPIO);
    gpio_init(LED_GREEN_GPIO);
    gpio_init(LED_BLUE_GPIO);

    gpio_set_dir(LED_RED_GPIO, GPIO_OUT);
    gpio_set_dir(LED_GREEN_GPIO, GPIO_OUT);
    gpio_set_dir(LED_BLUE_GPIO, GPIO_OUT);

}

int main()
{
    stdio_init_all();

    while (cyw43_arch_init())
    {
        while (true)
        {
            printf("Cyw43 did not load, stopping pico");
        }
    }


}
