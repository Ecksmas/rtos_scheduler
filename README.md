# RTOS Scheduler

## Overview

A lightweight cooperative RTOS style task scheduler written in C.
Designed for embedded systems such as a microcontroller, it allows multiple periodic and delayed tasks to run in a time-sliced fashion without a real operating system.

## Example

By default, the maximum number of tasks is __5__, but this can be adjusted in scheduler.c.

The example below runs on a regular host system to demonstrate the scheduler logic.
When using a __microcontroller__, replace the printf() calls with your platform’s SDK functions, for example, toggling a GPIO pin to blink an LED and initializing the GPIOs as needed.

If you are using an SDK other than the __Raspberry Pi Pico SDK__, you will also need to adjust the tick timing in scheduler_run() (currently implemented with sleep_ms()).

```
#include "scheduler.h"

void blink_led() {
    printf("LED toggled\n");
}

int main() {
    scheduler_init();
    Task led_task = create_task(blink_led, 1000);
    scheduler_add_task(led_task);
    scheduler_run();
    return 0;
}
```

## Testing

Doctest is used in the testing of the project, some simple test to check that everything is running correctly.

To run tests:
- cd build
- ./runTests