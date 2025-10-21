#include "scheduler.h"
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include "pico/stdlib.h"

#define MAX_TASKS 5

Task tasks[MAX_TASKS];
bool scheduler_running = true;

Task create_task(Task_Function f, int delay)
{
    Task t;
    t.fptr = f;
    t.delay = delay;
    t.period = delay;
    t.active = true;

    return t;
}

bool scheduler_add_task(Task task)
{
    for (size_t i = 0; i < MAX_TASKS; i++)
    {
        if (!tasks[i].active)
        {
            tasks[i] = task;
            tasks[i].delay = 0;
            return true;
        }
    }
    printf("Out of bounds in the scheduler_add_task function\n");
    return false;
}

void scheduler_delay_task(int i)
{
    tasks[i].delay = tasks[i].period;
}

void scheduler_end_task(Task *task)
{
    task->active = false;
}

void scheduler_init()
{
    for (size_t i = 0; i < MAX_TASKS; i++)
    {
        tasks[i].active = false;
    }
}

void scheduler_tick_once()
{
    while (scheduler_running)
    {
        for (size_t i = 0; i < MAX_TASKS; i++)
        {
            if (tasks[i].active && tasks[i].delay == 0)
            {
                tasks[i].fptr();
                scheduler_delay_task(i);
            }
            else if (tasks[i].active && tasks[i].delay > 0)
            {
                tasks[i].delay--;
            }
        }
    }
}

void scheduler_run()
{
    while (scheduler_running)
    {
        scheduler_tick_once();
        sleep_ms(1);
    }

}

bool scheduler_stop()
{
    if (scheduler_running)
    {
        scheduler_running = false;
        return true;
    }
    return false;
}

bool get_scheduler_running() {
    return scheduler_running;
}