#include <hidef.h>
#include "derivative.h"
#include "os.h"

#ifdef __cplusplus
extern "C"
#endif

void MCU_init();

cpu_t stk1[128];
cpu_t stk2[128];
cpu_t stk_idle[128];

void task1(){
    int i = 0;
    for(;;){
        i++;
        os_delay(10);
    }
}

void task2(){
    int i = 0;
    for(;;){
        i++;
        os_delay(10);
    }
}

void idle_task(){
    for(;;);
}

void main(){
    MCU_init();
    
#if (OS_SCHED==SCHED_PRIO)
    installTask(task1, stk1, sizeof(stk1), 1);
    installTask(task2, stk2, sizeof(stk2), 2);
    installTask(idle_task, stk_idle, sizeof(stk_idle), 0);
#else
    installTask(task1, stk1, sizeof(stk1));
    installTask(task2, stk2, sizeof(stk2));
    installTask(idle_task, stk_idle, sizeof(stk_idle));
#endif
    start_os();
    
    for(;;);
}
