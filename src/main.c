#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "scheduler.h"

#define LED_RED_GPIO 14
#define LED_GREEN_GPIO 13
#define LED_BLUE_GPIO 12

void gpio_setup(void)
{
    gpio_init(LED_RED_GPIO);
    gpio_init(LED_GREEN_GPIO);
    gpio_init(LED_BLUE_GPIO);

    gpio_set_dir(LED_RED_GPIO, GPIO_OUT);
    gpio_set_dir(LED_GREEN_GPIO, GPIO_OUT);
    gpio_set_dir(LED_BLUE_GPIO, GPIO_OUT);
}

void led_task_red()
{
    gpio_put(LED_RED_GPIO, !gpio_get(LED_RED_GPIO));
}

void led_task_green()
{
    gpio_put(LED_GREEN_GPIO, !gpio_get(LED_GREEN_GPIO));
}

void led_task_blue()
{
    gpio_put(LED_BLUE_GPIO, !gpio_get(LED_BLUE_GPIO));
}

int main()
{
    stdio_init_all();

    gpio_setup();

    scheduler_init();

    Task red = create_task(led_task_red, 1000);
    Task green = create_task(led_task_green, 1500);
    Task blue = create_task(led_task_blue, 1000);

    scheduler_add_task(red);
    scheduler_add_task(green);
    scheduler_add_task(blue);

    scheduler_run();

}
