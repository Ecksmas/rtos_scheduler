# Minimal RTOS Scheduler: Design Document

## Overview

The project is a minimal cooperative round robin scheduler with delays. The scheduler is lightweight and inteded and tested for the raspberry pi pico 2 w or other micro controllers with limited resources.

Primary goals:

- Run multiple tasks in a scheduler
- Have two of them *run* at the same time
- Remain minimal and easy to integrate

## Design Objectives

1. Simplicity: Minimize complexity to showcase understanding of the concepts
2. Predictability: Tasks run at defined intervals
3. Portability: Written in C with minimal depencies
4. Cooperative Scheduling: Task can not be overly complexed and must finish quickly

## Data Structure

```
typedef struct Task {
    Task_Function fptr;
    int delay;
    int period;
    bool active;
} Task;
```

- Each tasks has a pointer to the function
- Delay the users inputs (the task is run at the start and then delayed by the period)
- Period of how often the task should repeat
- Active flag to enable or disable the task

## Core Functions
### Task Management
```
Task create_task(Task_Function f, int delay);
```
Initializes a task to the struct Task.

```
bool scheduler_add_task(Task task);
```
Adds the task to the scheduler array/que, return success/failure if within bounds.

```
void scheduler_delay_task(int i);
```
Reassing the period to the delay once it has been decremented to 0.

```
void scheduler_end_task(Task *task);
```
Marks a task as inactive, removing it from future execution.

```
void scheduler_tick_once();
```
Runs the tasks once within the schedule_run function.

### Scheduler Control

```
void scheduler_init();
```
Intializes the array with default values that are inactive.

```
void scheduler_run();
```
Starts the main scheduler loop and iterates through the tasks and execute active ones.

```
void scheduler_stop();
```
Stops the scheduler loop by flipping a global variable, should be used inside a task function.

### Scheduler Flow

1. Intialization
    - Call scheduler_init()
    - Create and add tasks with create_task(task, delay) and scheduler_add_task(task)
2. Execution loop
    - If the assigned delay is larger than 0 the delay is decremented every tick
    - When the delay is 0 the function pointer is called upon, executed and delay reset
3. Stopping
    - Run scheduler_stop() to end the loop

## Limitations

- Tasks cannot be overly complicated or blocking (long execution, infinite loops etc.) as that will create stronger drift
- All tasks are equally created, as such you cannot priotize one task over the other
- Designed for demostration and not optimized for real-world critical real-time constraints

## Future Improvements

- Change the tick to a hardware timer for better accuarcy
- Add priorities for tasks
- Create a dynamic task array or que