#include "port.h"
#include "os_config.h"

#define SCHED_COOP 0
#define SCHED_PRIO 1

typedef struct {
    cpu_t* stk;
    cpu_t ready;
    long long timeout;
#if (OS_SCHED==SCHED_PRIO)
    cpu_t prio;
#endif
}TCB_t;

extern volatile TCB_t TCB[4];
extern volatile cpu_t ct;
extern volatile cpu_t it;
extern volatile long long os_time;

#if (OS_SCHED==SCHED_PRIO)
void installTask(task_t task, cpu_t *stack, int stack_size, cpu_t prio);
#else
void installTask(task_t task, cpu_t *stack, int stack_size);
#endif
void start_os();
cpu_t *scheduler();
void os_delay(long long time);

