#pragma once

#ifdef PICO_BUILD
#include "pico/stdlib.h"
#else
#include <windows.h>
#endif

static inline void platform_sleep_ms(int ms)
{
#ifdef PICO_BUILD
    sleep_ms(ms);
#else
    Sleep(ms);
#endif
}