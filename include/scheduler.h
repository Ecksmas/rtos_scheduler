#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef void (*Task_Function)();

typedef struct Task {
    Task_Function fptr;
    int delay;
    int period;
    bool active;
} Task;

Task create_task(Task_Function f, int delay);
bool scheduler_add_task(Task task);
void scheduler_delay_task(int i);
void scheduler_end_task(Task *task);
void scheduler_init();
void scheduler_run();
void scheduler_stop();


