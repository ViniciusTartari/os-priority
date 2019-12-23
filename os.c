#include "os.h"

volatile cpu_t ct = 0;
volatile cpu_t it = 0;
volatile TCB_t TCB[4];
volatile long long os_time = 0;

#if (OS_SCHED==SCHED_PRIO)
void installTask(task_t task, cpu_t *stack, int stack_size, cpu_t prio) {
#else
void installTask(task_t task, cpu_t *stack, int stack_size) {
#endif
    stack = (cpu_t*)((int)stack + stack_size - sizeof(cpu_t));
    stack = prepareStack(task,stack);
    TCB[it].stk = stack;
    TCB[it].ready = 1;
    #if (OS_SCHED == SCHED_PRIO)
    TCB[it].prio = prio;
    #endif
    it++;
}

void start_os(){
    init_os_timer();
    stk_tmp = TCB[0].stk;
    dispatcher();
}

cpu_t verify_task_ready(){
    cpu_t i = 0;
    cpu_t ready = 0;
    os_time++;
    for(i=0;i<it;i++){
        if(TCB[i].timeout == os_time){
            TCB[i].ready = 1;
            ready = 1;
        }
    }
    return ready;
}

cpu_t *scheduler(){
#if (OS_SCHED==SCHED_PRIO)
    cpu_t i = 0;
    cpu_t higher_prio = 0;
    cpu_t stask = 0;
    for(i=0;i<it;i++){
        if(TCB[i].prio >= higher_prio && TCB[i].ready){
            higher_prio = TCB[i].prio;
            stask = i;
        }
    }
    ct = stask;
    return TCB[ct].stk;
#else
    retry:
    ct++;
    if(ct>=it) ct=0;
    if(!TCB[ct].ready) goto retry;
    return TCB[ct].stk;
#endif
}

void os_delay(long long time){
    TCB[ct].timeout = os_time + time;
    TCB[ct].ready = 0;
    yield();
}
