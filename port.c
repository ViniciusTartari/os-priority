#include "os.h"

cpu_t *stk_tmp;

cpu_t* prepareStack(task_t task, cpu_t *stk){
    *stk-- = (cpu_t)((int)task & 0xFF);
    *stk-- = (cpu_t)((int)task >> 8);
    *stk-- = 0;
    *stk-- = 0;
    *stk-- = 0;
    *stk = 0;
    return stk;
}

interrupt void switchContext(){
    SAVE_SP();
    
    TCB[ct].stk = stk_tmp;
    stk_tmp = scheduler();
    
    RESTORE_SP();
}

void init_os_timer(){
    TPM1SC = 0x00;
    TPM1MOD = 19999;
    TPM1SC = 0x48;
}

interrupt void os_timer(){
    TPM1SC_TOF = 0;
    
    if(verify_task_ready()){
        SAVE_SP();
        
        TCB[ct].stk = stk_tmp;
        stk_tmp = scheduler();
        
        RESTORE_SP();
    }
}

