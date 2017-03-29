#include "cyg/hal/arch.inc"

#define CYGARC_JMP_BUF_SP        0
#define CYGARC_JMP_BUF_X8        1
#define CYGARC_JMP_BUF_X9        2
#define CYGARC_JMP_BUF_X18       3
#define CYGARC_JMP_BUF_X19       4
#define CYGARC_JMP_BUF_X20       5
#define CYGARC_JMP_BUF_X21       6
#define CYGARC_JMP_BUF_X22       7
#define CYGARC_JMP_BUF_X23       8
#define CYGARC_JMP_BUF_X24       9
#define CYGARC_JMP_BUF_X25      10
#define CYGARC_JMP_BUF_X26      11
#define CYGARC_JMP_BUF_X27      12

#define CYGARC_JMP_BUF_SIZE     13

    .global hal_thread_switch_context
hal_thread_switch_context:

    addi    sp, sp, -riscvreg_size #space for regs

    STORE   x1,  0  * riscv_regsize(sp)
	STORE	x2,  1  * riscv_regsize(sp)
	STORE	x3,  2  * riscv_regsize(sp)
	STORE	x4,  3  * riscv_regsize(sp)
	STORE	x5,  4  * riscv_regsize(sp)
	STORE	x6,  5  * riscv_regsize(sp)
	STORE	x7,  6  * riscv_regsize(sp)
	STORE	x8,  7  * riscv_regsize(sp)
	STORE	x9,  8  * riscv_regsize(sp)
	STORE	x10, 9  * riscv_regsize(sp)
	STORE	x11, 10 * riscv_regsize(sp)
	STORE	x12, 11 * riscv_regsize(sp)
	STORE	x13, 12 * riscv_regsize(sp)
	STORE	x14, 13 * riscv_regsize(sp)
	STORE	x15, 14 * riscv_regsize(sp)
	STORE	x16, 15 * riscv_regsize(sp)
	STORE	x17, 16 * riscv_regsize(sp)
	STORE	x18, 17 * riscv_regsize(sp)
	STORE	x19, 18 * riscv_regsize(sp)
	STORE	x20, 19 * riscv_regsize(sp)
	STORE	x21, 20 * riscv_regsize(sp)
	STORE	x22, 21 * riscv_regsize(sp)
	STORE	x23, 22 * riscv_regsize(sp)
	STORE	x24, 23 * riscv_regsize(sp)
	STORE	x25, 24 * riscv_regsize(sp)
	STORE	x26, 25 * riscv_regsize(sp)
	STORE	x27, 26 * riscv_regsize(sp)
	STORE	x28, 27 * riscv_regsize(sp)
	STORE	x29, 28 * riscv_regsize(sp)
	STORE	x30, 29 * riscv_regsize(sp)
	STORE	x31, 30 * riscv_regsize(sp)

# TODO: break below func on callee and caller macros
#ifdef CYGHWR_HAL_RISCV_FPU
    hal_fpu_save_regs sp
#endif

    csrr    t0, mepc
    STORE   t0, riscvreg_mepc(sp)

    csrr    t0, mstatus
    STORE   t0, riscvreg_mstatus(sp)

    STORE   sp, (a1) #save sp in location passed by second arg

    # Now load the destination thread by dropping through
    # to hal_thread_load_context

#--------------------------------------------------------
    .global hal_thread_load_context
hal_thread_load_context:

    LOAD    sp, (a0)

    LOAD    t0, riscvreg_mepc(sp)
    csrw    mepc, t0

    LOAD    t0, riscvreg_mstatus(sp)
    csrw    mstatus, t0

# TODO: break below func on callee and caller macros
#ifdef CYGHWR_HAL_RISCV_FPU
    hal_fpu_load_regs sp
#endif

    LOAD    x1,  0  * riscv_regsize(sp)
    LOAD    x2,  1  * riscv_regsize(sp)
    LOAD    x3,  2  * riscv_regsize(sp)
    LOAD    x4,  3  * riscv_regsize(sp)
    LOAD    x5,  4  * riscv_regsize(sp)
    LOAD    x6,  5  * riscv_regsize(sp)
    LOAD    x7,  6  * riscv_regsize(sp)
    LOAD    x8,  7  * riscv_regsize(sp)
    LOAD    x9,  8  * riscv_regsize(sp)
    LOAD    x10, 9  * riscv_regsize(sp)
    LOAD    x11, 10 * riscv_regsize(sp)
    LOAD    x12, 11 * riscv_regsize(sp)
    LOAD    x13, 12 * riscv_regsize(sp)
    LOAD    x14, 13 * riscv_regsize(sp)
    LOAD    x15, 14 * riscv_regsize(sp)
    LOAD    x16, 15 * riscv_regsize(sp)
    LOAD    x17, 16 * riscv_regsize(sp)
    LOAD    x18, 17 * riscv_regsize(sp)
    LOAD    x19, 18 * riscv_regsize(sp)
    LOAD    x20, 19 * riscv_regsize(sp)
    LOAD    x21, 20 * riscv_regsize(sp)
    LOAD    x22, 21 * riscv_regsize(sp)
    LOAD    x23, 22 * riscv_regsize(sp)
    LOAD    x24, 23 * riscv_regsize(sp)
    LOAD    x25, 24 * riscv_regsize(sp)
    LOAD    x26, 25 * riscv_regsize(sp)
    LOAD    x27, 26 * riscv_regsize(sp)
    LOAD    x28, 27 * riscv_regsize(sp)
    LOAD    x29, 28 * riscv_regsize(sp)
    LOAD    x30, 29 * riscv_regsize(sp)
    LOAD    x31, 30 * riscv_regsize(sp)
    
    eret
    
    .global hal_setjmp
hal_setjmp:
    STORE   x2, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x8, CYGARC_JMP_BUF_SP * riscv_regsize(a0)     
    STORE   x9, CYGARC_JMP_BUF_SP * riscv_regsize(a0)     
    STORE   x18, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x19, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x20, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x21, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x22, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x23, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x24, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x25, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x26, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    STORE   x27, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    li      a0, 0
    jr      ra
    
    .global hal_longjmp
hal_longjmp:
    LOAD    x2, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x8, CYGARC_JMP_BUF_SP * riscv_regsize(a0)     
    LOAD    x9, CYGARC_JMP_BUF_SP * riscv_regsize(a0)     
    LOAD    x18, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x19, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x20, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x21, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x22, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x23, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x24, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x25, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x26, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    LOAD    x27, CYGARC_JMP_BUF_SP * riscv_regsize(a0)   
    mv      a0, a1
    jr      ra
