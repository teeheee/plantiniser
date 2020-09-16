#ifndef _SCHEDULER_HAL_H_
#define _SCHEDULER_HAL_H_

class hal_scheduler {
public:
    virtual void init() = 0;
    virtual void run_task(int milliseconds, void (*func)(), int priority) = 0;
    virtual void process() = 0;
};

class hal_scheduler_impl : public hal_scheduler{
public:
    void init();
    void run_task(int milliseconds, void (*func)(), int priority);
    void process();
};

#endif