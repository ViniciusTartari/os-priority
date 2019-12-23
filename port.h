#include "derivative.h"

typedef unsigned char cpu_t;
typedef void (*task_t)();

extern cpu_t *stk_tmp;

#define yield() asm("swi");

#define SAVE_SP()   \
asm("TSX");         \
asm("STHX stk_tmp")

#define RESTORE_SP()\
asm("LDHX stk_tmp");\
asm("TXS")

#define dispatcher()\
asm("LDHX stk_tmp");\
asm("TXS");         \
asm("PULH");        \
asm("RTI")

cpu_t *prepareStack(task_t task, cpu_t *stk);
void init_os_timer;
