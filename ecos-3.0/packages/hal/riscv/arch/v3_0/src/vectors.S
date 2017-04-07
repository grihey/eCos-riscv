
#include <cyg/hal/arch.inc>

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
    /* init bss section */
    la	a0, _stack_end  /* note the stack grows from top to bottom */
    la	a1, _stack
    li	a2, 0xABABABAB
    jal	fill_block

init_stack:
    /* set stack pointer */
    la	sp, _stack

/*    .global plf_init, main
    ## platform init
10: auipc t0, %pcrel_hi(plf_init)
    jalr  t0, %pcrel_lo(10b)
    ## start main
11: auipc t0, %pcrel_hi(main)
    ## init argv=0, argc=0
    li a0, 0
    li a1, 0
    jalr  t0, %pcrel_lo(11b) */
    jal   cyg_start

.previous

    .global trap_handler
    .weak trap_handler
trap_handler:
    ret

halt_loop:
    wfi
    j     halt_loop

/* When trap is an interrupt, this function is called */
interrupt:
	srli	t0,t0,1
	beq		t0,x0,softwareInterrupt
	LOAD	t0, 0x0(sp)
	addi	sp, sp, riscv_regsize

	/* Interupt is timer interrupt */
	/* j		TIMER_CMP_INT */
	eret
softwareInterrupt:
	/* Interupt is software interrupt */
	eret


/* For when a trap is fired */
trap_entry:
	/* Check for interrupt */
	addi	sp, sp, -riscv_regsize
	STORE	t0, 0x0(sp)
	csrr	t0, mcause
	blt	t0,x0,interrupt
	LOAD	t0, 0x0(sp)
	addi	sp, sp, riscv_regsize

	/* System call and other traps */
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

	csrr a0, mcause
	csrr a1, mepc

	mv a2, sp
	jal trap_handler

	csrw mepc, a0

	LOAD x1, 0*riscv_regsize(sp)
	LOAD x2, 1*riscv_regsize(sp)
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

	addi sp, sp, riscvreg_size
	eret

/* Fills memory blocks */
fill_block:
    sw		a2, 0(a0)
    bgeu	a0, a1, fb_end
    addi	a0, a0, 4
    j		fill_block
fb_end:
    ret

    .section ".fixed_vectors"
// Space for the virtual vectors        
    .balign 4
// Vectors used to communicate between eCos and ROM environments
    .globl  hal_virtual_vector_table
hal_virtual_vector_table:
    .rept   64                  // CYGNUM_CALL_IF_TABLE_SIZE
    .long   0
    .endr
    .previous

	.extern hal_default_isr
	
	.data

	.globl	hal_interrupt_handlers
hal_interrupt_handlers:
	.long	hal_default_isr
	.long	hal_default_isr
	.long	hal_default_isr
	.long	hal_default_isr
	.long	hal_default_isr
	.long	hal_default_isr


	.globl	hal_interrupt_data
hal_interrupt_data:
	.rept	6
	.long	0
	.endr

	.globl	hal_interrupt_objects
hal_interrupt_objects:
	.rept	6
	.long	0
	.endr
