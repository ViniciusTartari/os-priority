#include "derivative.h"

typedef unsigned char cpu_t;
typedef void (*task_t)();

extern cpu_t *stk_tmp;

#define yield() asm("TRAP %0");

#define SAVE_SP()   \
asm("MOVE A7,stk_tmp");

#define RESTORE_SP()\
asm("MOVE stk_tmp,A7");

#define SAVE_CONTEXT() \
asm("LEA -40(A7),A7");\
asm("MOVEM.L (A7),D3-D7/A2-A6")


#define RESTORE_CONTEXT() \
asm("MOVEM.L (A7),D3-D7/A2-A6");\
asm("LEA 40(A7),A7")

#define dispatcher()\
asm("MOVE stk_tmp,A7");\
asm("MOVEM.L (A7),D3-D7/A2-A6");\
asm("LEA 40(A7),A7");\
asm("MOVEM.L (A7),D0-D2/A0-A1");\
asm("LEA 20(A7),A7");\
asm("RTE")


cpu_t *prepareStack(task_t task, cpu_t *stk);
void init_os_timer;

