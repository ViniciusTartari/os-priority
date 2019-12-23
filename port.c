#include "os.h"

cpu_t *stk_tmp;

cpu_t* prepareStack(task_t task, cpu_t *stk){
    *stk-- = (cpu_t)task;
    *stk-- = 0x40002000;
    *stk-- = 0xA1;
    *stk-- = 0xA0;
    *stk-- = 0xD2;
    *stk-- = 0xD1;
    *stk-- = 0xD0;
    *stk-- = 0xA6;
    *stk-- = 0xA5;
    *stk-- = 0xA4;
    *stk-- = 0xA3;
    *stk-- = 0xA2;
    *stk-- = 0xD7;
    *stk-- = 0xD6;
    *stk-- = 0xD5;
    *stk-- = 0xD4;
    *stk = 0xD3;
    return stk;
}

interrupt void switchContext(){
    SAVE_CONTEXT();
    SAVE_SP();
    
    TCB[ct].stk = stk_tmp;
    stk_tmp = scheduler();
    
    RESTORE_SP();
    RESTORE_CONTEXT();
}

void init_os_timer(){
    TPM1SC = 0x00;
    TPM1MOD = 19999;
    TPM1SC = 0x48;
}

interrupt void os_timer(){
    TPM1SC_TOF = 0;
    
    if(verify_task_ready()){
        SAVE_CONTEXT();
        SAVE_SP();
        
        TCB[ct].stk = stk_tmp;
        stk_tmp = scheduler();
        
        RESTORE_SP();
	RESTORE_CONTEXT();
    }
}

