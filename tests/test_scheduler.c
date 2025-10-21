#include "unity.h"
#include "scheduler.h"

static int task_ran = 0;

void dummy_task()
{
    task_ran++;
    if (task_ran == 5) scheduler_stop();
}

void setUp(void)
{
    scheduler_init();
}

void tearDown(void) {}

void test_create_task(void)
{
    Task t = create_task(dummy_task, 1000);

    TEST_ASSERT_NOT_NULL(t.fptr);
    TEST_ASSERT_EQUAL_INT(1000, t.delay);
    TEST_ASSERT_EQUAL_INT(1000, t.period);
    TEST_ASSERT_TRUE(t.active);
}

void test_add_task_succeed(void)
{
    Task t = create_task(dummy_task, 1000);
    bool added = scheduler_add_task(t);
    TEST_ASSERT_TRUE(added);
}

void test_run_task(void)
{
    Task t = create_task(dummy_task, 0);
    scheduler_add_task(t);

    scheduler_tick_once();
    TEST_ASSERT_EQUAL_INT(1, task_ran);
}

void test_scheduler_delay(void)
{
    int test_ticks = 3;
    Task t = create_task(dummy_task, 3);

    for (size_t i = 0; i < test_ticks; i++)
    {
        scheduler_tick_once();
    }

    TEST_ASSERT_EQUAL_INT(1, task_ran);
}

void test_end_task_stop_scheduler(void)
{
    Task t = create_task(dummy_task, 0);
    scheduler_add_task(t);

    Task *ptr = &t;
    scheduler_end_task(ptr);

    TEST_ASSERT_FALSE(t.active);
}

void test_stop_scheduler(void)
{
    // Let the task run for 5 ticks and it should stop the scheduler
    Task t = create_task(dummy_task, 0);
    scheduler_add_task(t);

    scheduler_run();

    TEST_ASSERT_TRUE(get_scheduler_running);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_create_task);
    RUN_TEST(test_add_task_succeed);
    RUN_TEST(test_run_task);
    RUN_TEST(test_scheduler_delay);
    RUN_TEST(test_end_task_stop_scheduler);
    RUN_TEST(test_stop_scheduler);

    return UNITY_END();
}
