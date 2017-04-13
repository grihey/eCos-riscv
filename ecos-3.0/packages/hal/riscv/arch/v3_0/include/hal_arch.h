#ifndef CYGONCE_HAL_HAL_ARCH_H
#define CYGONCE_HAL_HAL_ARCH_H

//==========================================================================
//
//      hal_arch.h
//
//      Architecture specific abstractions
//
//==========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    grihey
// Contributors: 
// Date:         2017-03-22
// Purpose:      Define architecture abstractions
// Usage:        #include <cyg/hal/hal_arch.h>
//              
//####DESCRIPTIONEND####
//
//==========================================================================

#ifndef __ASSEMBLER__
#include <pkgconf/hal.h>
#include <cyg/infra/cyg_type.h>


//#include <cyg/hal/var_arch.h>

//--------------------------------------------------------------------------
// Processor saved states:
// The layout of this structure is also defined in "arch.inc", for assembly
// code. Do not change this without changing that (or vice versa).
// Notes: This structure is carefully laid out. It is a multiple of 8
// bytes and the pc and badvr fields are positioned to ensure that
// they are on 8 byte boundaries. 
#ifdef CYGHWR_HAL_RISCV_64BIT
# define CYG_HAL_RISCV_REG CYG_WORD64
# define CYG_HAL_RISCV_REG_SIZE 8
#else
# define CYG_HAL_RISCV_REG CYG_WORD32
# define CYG_HAL_RISCV_REG_SIZE 4
#endif //CYGHWR_HAL_RISCV_64BIT

#ifdef CYGHWR_HAL_RISCV_FPU
# ifdef CYGHWR_HAL_RISCV_FPU_64BIT
#  define CYG_HAL_RISCV_FPU_REG CYG_WORD64
#  define CYG_HAL_RISCV_FPU_REG_SIZE 8
# else
#  define CYG_HAL_RISCV_FPU_REG CYG_WORD32
#  define CYG_HAL_RISCV_FPU_REG_SIZE 4
# endif //CYGHWR_HAL_RISCV_FPU_64BIT
#endif //CYGHWR_HAL_RISCV_FPU


typedef struct 
{
    CYG_HAL_RISCV_REG    d[31];          /* Data regs                    */
#ifdef CYGHWR_HAL_RISCV_FPU
    CYG_HAL_RISCV_FPU_REG f[32];
#endif
    CYG_WORD32           mstatus;               /* Status Reg                   */
    CYG_HAL_RISCV_REG    mepc;                  /* Mepc of memcall */
} HAL_SavedRegisters;


//--------------------------------------------------------------------------
// Bit manipulation macros

externC cyg_uint32 hal_lsbit_index(cyg_uint32 mask);
externC cyg_uint32 hal_msbit_index(cyg_uint32 mask);

#define HAL_LSBIT_INDEX(index, mask) index = hal_lsbit_index(mask);
#define HAL_MSBIT_INDEX(index, mask) index = hal_msbit_index(mask);


#ifdef CYGHWR_HAL_RISCV_FPU
#define HAL_THREAD_INIT_FPU_CONTEXT( _regs_, _id_ )                             \
{                                                                               \
    for( _i_ = 0; _i_ < 32; _i_++ ) (_regs_)->f[_i_] = 0x00000000;       \
}
#else
#define HAL_THREAD_INIT_FPU_CONTEXT( _regs_, _id_ )
#endif //CYGHWR_HAL_RISCV_FPU

//--------------------------------------------------------------------------
// Context Initialization

// Initialize the context of a thread.
// Arguments:
// _sparg_ name of variable containing current sp, will be written with new sp
// _thread_ thread object address, passed as argument to entry point
// _entry_ entry point address.
// _id_ bit pattern used in initializing registers, for debugging.
#define HAL_THREAD_INIT_CONTEXT( _sparg_, _thread_, _entry_, _id_ )                     \
{                                                                                       \
    register CYG_WORD _sp_ = ((CYG_WORD)_sparg_) & ~15;                                 \
    register HAL_SavedRegisters *_regs_;                                                \
    int _i_;                                                                            \
    _regs_ = (HAL_SavedRegisters *)(((_sp_) - sizeof(HAL_SavedRegisters))&0xFFFFFFF0);  \
    for( _i_ = 0; _i_ < 31; _i_++ ) (_regs_)->d[_i_] = 0x00000000;                      \
    HAL_THREAD_INIT_FPU_CONTEXT( _regs_, _id_ );                                        \
    (_regs_)->d[0] = (CYG_HAL_RISCV_REG)(_entry_);    /* x1 = RA = entry point  */      \
    (_regs_)->d[1] = (CYG_HAL_RISCV_REG)(_sp_);       /* x2 = SP = top of stack */      \
    (_regs_)->d[3] = (CYG_HAL_RISCV_REG)(_thread_);   /* x4 = arg1 = thread ptr */      \
    (_regs_)->d[9] = (CYG_HAL_RISCV_REG)(_thread_);   /* x10 = arg0 for thread_entry*/      \
    (_regs_)->mstatus = 0x00000006;                   /* SR = mmode in PRV1, int: dis         */      \
    (_regs_)->mepc = 0x00000000;                   /* SR = int en  1         */      \
    _sparg_ = (CYG_ADDRESS)_regs_;                                                      \
}

//--------------------------------------------------------------------------
// HAL setjmp
// Note: These definitions are repeated in hal_arch.h. If changes are
// required remember to update both sets.
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

typedef CYG_HAL_RISCV_REG hal_jmp_buf[CYGARC_JMP_BUF_SIZE];

externC int hal_setjmp(hal_jmp_buf env);
externC void hal_longjmp(hal_jmp_buf env, int val);

//--------------------------------------------------------------------------
// Context switch macros.
// The arguments are pointers to locations where the stack pointer
// of the current thread is to be stored, and from where the sp of the
// next thread is to be fetched.

externC void hal_thread_switch_context( CYG_ADDRESS to, CYG_ADDRESS from );
externC void hal_thread_load_context( CYG_ADDRESS to )
    __attribute__ ((noreturn));

#define HAL_THREAD_SWITCH_CONTEXT(_fspptr_,_tspptr_)                    \
        hal_thread_switch_context( (CYG_ADDRESS)_tspptr_,               \
                                   (CYG_ADDRESS)_fspptr_);

#define HAL_THREAD_LOAD_CONTEXT(_tspptr_)                               \
        hal_thread_load_context( (CYG_ADDRESS)_tspptr_ );

//--------------------------------------------------------------------------
// Idle thread code.
// This macro is called in the idle thread loop, and gives the HAL the
// chance to insert code. Typical idle thread behaviour might be to halt the
// processor. Here we only supply a default fallback if the variant/platform
// doesn't define anything.

#ifndef HAL_IDLE_THREAD_ACTION
#define HAL_IDLE_THREAD_ACTION(_count_) CYG_EMPTY_STATEMENT
#endif

//--------------------------------------------------------------------------
// Execution reorder barrier.
// When optimizing the compiler can reorder code. In multithreaded systems
// where the order of actions is vital, this can sometimes cause problems.
// This macro may be inserted into places where reordering should not happen.
// The "memory" keyword is potentially unnecessary, but it is harmless to
// keep it.

#define HAL_REORDER_BARRIER() asm volatile ( "" : : : "memory" )

//--------------------------------------------------------------------------
// Minimal and sensible stack sizes: the intention is that applications
// will use these to provide a stack size in the first instance prior to
// proper analysis.  Idle thread stack should be this big.

//    THESE ARE NOT INTENDED TO BE MICROMETRICALLY ACCURATE FIGURES.
//           THEY ARE HOWEVER ENOUGH TO START PROGRAMMING.
// YOU MUST MAKE YOUR STACKS LARGER IF YOU HAVE LARGE "AUTO" VARIABLES!

// This is not a config option because it should not be adjusted except
// under "enough rope" sort of disclaimers.

// Typical case stack frame size: return link + 4 pushed registers + some locals.
#define CYGNUM_HAL_STACK_FRAME_SIZE (48)

// Stack needed for a context switch:
#ifdef CYGHWR_HAL_RISCV_FPU
# define CYGNUM_HAL_STACK_CONTEXT_SIZE (((31+2)*CYG_HAL_RISCV_REG_SIZE)+(32*CYG_HAL_RISCV_FPU_REG_SIZE))
#else
# define CYGNUM_HAL_STACK_CONTEXT_SIZE ((31+2)*CYG_HAL_RISCV_REG_SIZE)
#endif //CYGHWR_HAL_RISCV_FPU

// Interrupt + call to ISR, interrupt_end() and the DSR
#define CYGNUM_HAL_STACK_INTERRUPT_SIZE (4+2*CYGNUM_HAL_STACK_CONTEXT_SIZE) 

#ifdef CYGIMP_HAL_COMMON_INTERRUPTS_USE_INTERRUPT_STACK

// An interrupt stack which is large enough for all possible interrupt
// conditions (and only used for that purpose) exists.  "User" stacks
// can be much smaller

#define CYGNUM_HAL_STACK_SIZE_MINIMUM (CYGNUM_HAL_STACK_CONTEXT_SIZE+      \
                                       CYGNUM_HAL_STACK_INTERRUPT_SIZE*2+  \
                                       CYGNUM_HAL_STACK_FRAME_SIZE*8)
#define CYGNUM_HAL_STACK_SIZE_TYPICAL (CYGNUM_HAL_STACK_SIZE_MINIMUM+1024)

#else // CYGIMP_HAL_COMMON_INTERRUPTS_USE_INTERRUPT_STACK 

// No separate interrupt stack exists.  Make sure all threads contain
// a stack sufficiently large.

#define CYGNUM_HAL_STACK_SIZE_MINIMUM (4096)
#define CYGNUM_HAL_STACK_SIZE_TYPICAL (4096)

#endif //CYGIMP_HAL_COMMON_INTERRUPTS_USE_INTERRUPT_STACK 

#define HAL_THREAD_GET_SAVED_REGISTERS( _sp_, _regs_ )          \
        (_regs_) = (HAL_SavedRegisters *)(_sp_)

#define HAL_QUERY_INTERRUPTS( _state_ )         \
{                                               \
    asm volatile (                              \
        "nop"                        \
        );                                      \
}

// Copy a set of registers from a HAL_SavedRegisters structure into a
// GDB ordered array.    
#define HAL_GET_GDB_REGISTERS( _aregval_ , _regs_ )             

// Copy a GDB ordered array into a HAL_SavedRegisters structure.
#define HAL_SET_GDB_REGISTERS( _aregval_ , _regs_ )             

//--------------------------------------------------------------------------
// Vector translation.

#ifndef HAL_TRANSLATE_VECTOR
#define HAL_TRANSLATE_VECTOR(_vector_,_index_) \
    (_index_) = (_vector_)
#endif //HAL_TRANSLATE_VECTOR

#endif // __ASSEMBLER__


//--------------------------------------------------------------------------
#endif // CYGONCE_HAL_HAL_ARCH_H
// End of hal_arch.h
