### Syntacore SCR* infra
###
### @copyright (C) Syntacore 2015-2016. All rights reserved.
### @author mn-sc
###
### @brief simple CRT entry

    ## some useful macros
    .altmacro

    .macro save_reg_offs reg, offs, save_mem_base=zero
#ifdef __riscv64
    sd   \reg, \offs*8(\save_mem_base)
#else
    sw   \reg, \offs*4(\save_mem_base)
#endif // __riscv64
    .endm

    .macro save_reg regn, save_mem_base=zero
#ifdef __riscv64
    sd   x\regn, \regn*8(\save_mem_base)
#else
    sw   x\regn, \regn*4(\save_mem_base)
#endif // __riscv64
    .endm

    .macro load_reg_offs reg, offs, load_mem_base=zero
#ifdef __riscv64
    ld   \reg, \offs*8(\load_mem_base)
#else
    lw   \reg, \offs*4(\load_mem_base)
#endif // __riscv64
    .endm

    .macro load_reg regn, load_mem_base=zero
#ifdef __riscv64
    ld   x\regn, \regn*8(\load_mem_base)
#else
    lw   x\regn, \regn*4(\load_mem_base)
#endif // __riscv64
    .endm

    .macro save_regs reg_first, reg_last, save_mem_base=zero
    LOCAL regn
    regn = \reg_first
    .rept \reg_last - \reg_first + 1
    save_reg %(regn), \save_mem_base
    regn = regn+1
    .endr
    .endm

    .macro load_regs reg_first, reg_last, load_mem_base=zero
    LOCAL regn
    regn = \reg_first
    .rept \reg_last - \reg_first + 1
    load_reg %(regn), \load_mem_base
    regn = regn+1
    .endr
    .endm

#define TRAP_STACK_SPACE 512
#define TRAP_REGS_SPACE 512

    .globl _start
    .globl main
    .globl handle_trap
    .weak handle_trap

    ## .text
    .option norvc
##.section ".text.crt","ax",@progbits

    .align 6
user_trap_entry:
    j trap_entry

    .align 6
supervisor_trap_entry:
    j trap_entry

    .align 6
hypervisor_trap_entry:
    j trap_entry

    .align 6
machine_trap_entry:
    j trap_entry

    .align 6
_start:
    la  a0, user_trap_entry
    csrw mtvec, a0

    ## la    a0, __reloc_start
    ## la    a1, __TEXT_START__
    la    a2, __BSS_START__
    ## beq   a0, a1, 21f
    ## j     2f
## 1:  lw    a3, 0(a0)
##     sw    a3, 0(a1)
##     add   a0, a0, 4
##     add   a1, a1, 4
## 2:  bne   a1, a2, 1b
    # clear bss
21: la    a1, __BSS_END__
    j     4f
3:  sw    zero, 0(a2)
    add   a2, a2, 4
4:  bne   a1, a2, 3b
    la    gp, _gp
    ## init stack
    la    sp, __C_STACK_TOP__ - TRAP_REGS_SPACE
    csrw  mscratch, sp
    addi  sp, sp, -TRAP_STACK_SPACE
    ## init hart0 TLS
    la    a0, _tdata_begin
    la    a2, _tbss_end
    sub   a1, a2, a0
    la    a4, __STACK_START__
    sub   tp, a4, a1
    ## init tdata
    mv    a1, tp
    la    a2, _tdata_end
    j     6f
5:  lw    a3, 0(a0)
    sw    a3, 0(a1)
    add   a0, a0, 4
    add   a1, a1, 4
6:  bne   a0, a2, 5b
    ## clear tbss
    j     8f
7:  sw    zero, 0(a1)
    add   a1, a1, 4
8:  bne   a1, a4, 7b
    ## init timer for RTC_HZ clock
    csrw  0x7b4, s1
    ## init FPU (if supported)
    csrr  a0, mcpuid
    bgez  a1, 9f
    li    a0, 0x00001000
    csrs  mstatus, a0
    csrw  fcsr, zero
9:
    ## platform init
    .global plf_init
10: auipc t0, %pcrel_hi(plf_init)
    jalr  t0, %pcrel_lo(10b)
    ## start main
11: auipc t0, %pcrel_hi(main)
    ## init argv=0, argc=0
    li a0, 0
    li a1, 0
    jalr  t0, %pcrel_lo(11b)
    ## store result
handle_trap:
    ## lui    s1, %hi(__PLATFORM_ERR_CODE_ADDR)
    ## addi   s1, s1, %lo(__PLATFORM_ERR_CODE_ADDR)
    ## sw    a0, 0(s1)
halt_loop:
    wfi
    j     halt_loop

trap_entry:
    eret
