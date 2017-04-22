
#include <cyg/hal/arch.inc>
#include <pkgconf/hal.h>
#include <cyg/hal/hal_intr.h>

.section ".trap_vectors","ax"
	.align 6
user_trap_entry:
	j	trap_entry

	.align 6
supervisor_trap_entry:
	j	trap_entry

	.align 6
hypervisor_trap_entry:
	j	trap_entry

	.align 6
machine_trap_entry:
	j	trap_entry


	.align 6

    .section ".reset_vector","ax"
    .weak reset_vector
/* Startup code */
reset_vector:
    /* init regs */
    li	x1, 0
    li	x2, 0
    li	x3, 0
    li	x4, 0
    li	x5, 0
	li	x6, 0
    li	x7, 0
    li	x8, 0
    li	x9, 0
    li	x10, 0
    li	x11, 0
    li	x12, 0
    li	x13, 0
    li	x14, 0
    li	x15, 0
    li	x16, 0
    li	x17, 0
    li	x18, 0
    li	x19, 0
    li	x20, 0
    li	x21, 0
    li	x22, 0
    li	x23, 0
    li	x24, 0
    li	x25, 0
    li	x26, 0
    li	x27, 0
    li	x28, 0
    li	x29, 0
    li	x30, 0
    li	x31, 0

    /* initialize global pointer */
    la	gp, _gp

    /* init mtvec */
    la  a0, user_trap_entry
    csrw mtvec, a0

init_bss:
    /* init bss section */
    la	a0, __bss_start
    la	a1, __bss_end
    li	a2, 0x0
    jal	fill_block

write_stack_pattern:
    la	a0, _interrupt_stack_end  /* note the stack grows from top to bottom */
    la	a1, _interrupt_stack
    li	a2, 0x0
    jal	fill_block

init_stack:
    /* set stack pointer */
    la	sp, _interrupt_stack

	# Call constructors
	.extern cyg_hal_invoke_constructors
	jal     cyg_hal_invoke_constructors

    jal   cyg_start

.previous

halt_loop:
    wfi
    j     halt_loop

/* For when a trap is fired */
trap_entry:

	addi sp, sp, -riscvreg_size
	STORE x1, 0*riscv_regsize(sp)
	STORE x2, 1*riscv_regsize(sp)
	STORE x3, 2*riscv_regsize(sp)
	STORE x4, 3*riscv_regsize(sp)
	STORE x5, 4*riscv_regsize(sp)
	STORE x6, 5*riscv_regsize(sp)
	STORE x7, 6*riscv_regsize(sp)
	STORE x8, 7*riscv_regsize(sp)
	STORE x9, 8*riscv_regsize(sp)
	STORE x10, 9*riscv_regsize(sp)
	STORE x11, 10*riscv_regsize(sp)
	STORE x12, 11*riscv_regsize(sp)
	STORE x13, 12*riscv_regsize(sp)
	STORE x14, 13*riscv_regsize(sp)
	STORE x15, 14*riscv_regsize(sp)
	STORE x16, 15*riscv_regsize(sp)
	STORE x17, 16*riscv_regsize(sp)
	STORE x18, 17*riscv_regsize(sp)
	STORE x19, 18*riscv_regsize(sp)
	STORE x20, 19*riscv_regsize(sp)
	STORE x21, 20*riscv_regsize(sp)
	STORE x22, 21*riscv_regsize(sp)
	STORE x23, 22*riscv_regsize(sp)
	STORE x24, 23*riscv_regsize(sp)
	STORE x25, 24*riscv_regsize(sp)
	STORE x26, 25*riscv_regsize(sp)
	STORE x27, 26*riscv_regsize(sp)
	STORE x28, 27*riscv_regsize(sp)
	STORE x29, 28*riscv_regsize(sp)
	STORE x30, 29*riscv_regsize(sp)
	STORE x31, 30*riscv_regsize(sp)

#ifdef CYGHWR_HAL_RISCV_FPU
    hal_fpu_save_regs sp
#endif //CYGHWR_HAL_RISCV_FPU

	csrr    t0, mstatus
    STORE   t0, riscvreg_mstatus(sp)
	csrr    t0, mepc
    STORE   t0, riscvreg_mepc(sp)

#ifdef CYGFUN_HAL_COMMON_KERNEL_SUPPORT			
	.extern	cyg_scheduler_sched_lock
	la	    t0,cyg_scheduler_sched_lock
	lw	    t1,0(t0)
	addi	t1, t1, 1
	sw	    t1,0(t0)
#endif

#ifdef CYGIMP_HAL_COMMON_INTERRUPTS_USE_INTERRUPT_STACK	
    mv      t0, sp
    la      sp, _interrupt_stack
    addi    sp, sp, -riscv_regsize
    STORE   t0, 0(sp)
#endif //CYGIMP_HAL_COMMON_INTERRUPTS_USE_INTERRUPT_STACK	

    .extern trap_handler_diag
    .extern interrupt_end

trap_handler:

    csrr    t1, mcause 
    mv      a0, t1

    jal     trap_handler_diag

    csrr    t1, mcause 

    // if interrupt handle it, if not  restore sp and exit
    bltz    t1, 1f
    LOAD    sp, (sp)    
    j       restore_context

1:  
    andi    t1, t1, 0xf
    mv      a0, t1

    //TODO: 2 should be a parameter related to regsize
    slli    t1, t1, 2

    la      a1, hal_interrupt_data
    add     a1, a1, t1
    LOAD    a1, (a1)
    la      t2, hal_interrupt_handlers
    add     t2, t2, t1
    LOAD    t2, (t2)

    //TODO: delete after debuging
    csrw    mtimecmp, 0
    jalr    t2

    la      a1, hal_interrupt_objects
    add     a1, a1, t1
    LOAD    a1, (a1)

    LOAD    a2, (sp) 

    //return thread stack pointer cause context may switching
    mv      sp, a2
    // a0 already have isr answer
    jal     interrupt_end

restore_context:

    LOAD    t0, riscvreg_mstatus(sp)
	csrw    mstatus, t0
    LOAD    t0, riscvreg_mepc(sp)
	csrw    mepc, t0

#ifdef CYGHWR_HAL_RISCV_FPU
    hal_fpu_load_regs sp
#endif //CYGHWR_HAL_RISCV_FPU

	LOAD x1, 0*riscv_regsize(sp)
	LOAD x3, 2*riscv_regsize(sp)
	LOAD x4, 3*riscv_regsize(sp)
	LOAD x5, 4*riscv_regsize(sp)
	LOAD x6, 5*riscv_regsize(sp)
	LOAD x7, 6*riscv_regsize(sp)
	LOAD x8, 7*riscv_regsize(sp)
	LOAD x9, 8*riscv_regsize(sp)
	LOAD x10, 9*riscv_regsize(sp)
	LOAD x11, 10*riscv_regsize(sp)
	LOAD x12, 11*riscv_regsize(sp)
	LOAD x13, 12*riscv_regsize(sp)
	LOAD x14, 13*riscv_regsize(sp)
	LOAD x15, 14*riscv_regsize(sp)
	LOAD x16, 15*riscv_regsize(sp)
	LOAD x17, 16*riscv_regsize(sp)
	LOAD x18, 17*riscv_regsize(sp)
	LOAD x19, 18*riscv_regsize(sp)
	LOAD x20, 19*riscv_regsize(sp)
	LOAD x21, 20*riscv_regsize(sp)
	LOAD x22, 21*riscv_regsize(sp)
	LOAD x23, 22*riscv_regsize(sp)
	LOAD x24, 23*riscv_regsize(sp)
	LOAD x25, 24*riscv_regsize(sp)
	LOAD x26, 25*riscv_regsize(sp)
	LOAD x27, 26*riscv_regsize(sp)
	LOAD x28, 27*riscv_regsize(sp)
	LOAD x29, 28*riscv_regsize(sp)
	LOAD x30, 29*riscv_regsize(sp)
	LOAD x31, 30*riscv_regsize(sp)
	LOAD x2,  1*riscv_regsize(sp)

    addi    sp, sp, riscvreg_size
	eret

/* Fills memory blocks */
fill_block:
    sw		a2, 0(a0)
    bgeu	a0, a1, fb_end
    addi	a0, a0, 4
    j		fill_block
fb_end:
    ret


    /*empty*/
    .globl __default_interrupt_vsr
__default_interrupt_vsr:
    ret

    .globl __default_exception_vsr
__default_exception_vsr:
    ret

##-----------------------------------------------------------------------------
## Interrupt Stack.
## Used during intialization and for executing ISRs.
	
    .section ".int_stack"

	.balign 16
	.global cyg_interrupt_stack_base
cyg_interrupt_stack_base:
_interrupt_stack_end:
	.rept CYGNUM_HAL_COMMON_INTERRUPTS_STACK_SIZE
	.byte 0
	.endr
	.balign 16
	.global cyg_interrupt_stack
cyg_interrupt_stack:
_interrupt_stack:

	.long	0,0,0,0,0,0,0,0	
    .previous

	.data
	.globl	hal_vsr_table

hal_vsr_table:	
	.long	__default_interrupt_vsr	
	.rept	63
	.long	__default_exception_vsr	
	.endr
    .previous

// Space for the virtual vectors        
// Vectors used to communicate between eCos and ROM environments
    .globl  hal_virtual_vector_table
hal_virtual_vector_table:
    .rept   64                  // CYGNUM_CALL_IF_TABLE_SIZE
    .long   0
    .endr
    .previous

//Interrupt handlers and related arrays
	.extern hal_default_isr
	
	.data

	.globl	hal_interrupt_handlers
hal_interrupt_handlers:
	.rept   CYGNUM_HAL_ISR_COUNT
	.long	hal_default_isr
	.endr

	.globl	hal_interrupt_data
hal_interrupt_data:
	.rept   CYGNUM_HAL_ISR_COUNT
	.long	0
	.endr

	.globl	hal_interrupt_objects
hal_interrupt_objects:
	.rept	CYGNUM_HAL_ISR_COUNT
	.long	0
	.endr
