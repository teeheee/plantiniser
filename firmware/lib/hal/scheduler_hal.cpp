#ifndef __TEST__

#include "scheduler_hal.h"
#include <TaskScheduler.h>
#include <list>

Scheduler runner;
std::list<Task*> TaskList;

void hal_scheduler_impl::init()
{
    runner.init();
}

void hal_scheduler_impl::run_task(int milliseconds, void (*func)(), int priority)
{
    Task* p_task = new Task(milliseconds, TASK_FOREVER, func);
    runner.addTask(*p_task);
    TaskList.push_front(p_task);
}

void hal_scheduler_impl::process()
{
    static int first_run = 1;
    if(first_run)
    {
        for(const auto& p_task : TaskList)
        {
            p_task->enable();
        }
        first_run = 0;
    }
    runner.execute();
}

#endif
