//==========================================================================
//
//      hal_misc.c //
//      HAL miscellaneous functions
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
// Purpose:      HAL miscellaneous functions
// Description:  This file contains miscellaneous functions provided by the
//               HAL.
//
//####DESCRIPTIONEND####
//
//========================================================================*/

#include <pkgconf/hal.h>

#include <cyg/infra/cyg_type.h>         // Base types
#include <cyg/infra/cyg_trac.h>         // tracing macros
#include <cyg/infra/cyg_ass.h>          // assertion macros
#include <cyg/infra/diag.h>

#include <cyg/hal/hal_arch.h>           // architectural definitions

#include <cyg/hal/hal_intr.h>           // Interrupt handling
// #include <cyg/hal/hal_cache.h>          // Cache handling
 #include <cyg/hal/hal_if.h>             // hal_ctrlc_isr()


cyg_uint32 hal_msbit_index(cyg_uint32 mask)
{
    int i;
    for (i = 31;  i >= 0;  i--) {
      if (mask & (1<<i)) return (i);
    }
    return (-1);
}

cyg_uint32 hal_lsbit_index(cyg_uint32 mask)
{
    int i;
    for (i = 0;  i < 32;  i++) {
      if (mask & (1<<i)) return (i);
    }
    return (-1);
}

externC cyg_uint32 hal_arch_default_isr(CYG_ADDRWORD vector, CYG_ADDRWORD data)
{
    return 0;
}

typedef void (*pfunc) (void);
extern pfunc __init_array_start[];
extern pfunc __init_array_end[];

void
cyg_hal_invoke_constructors(void)
{
#ifdef CYGSEM_HAL_STOP_CONSTRUCTORS_ON_FLAG
    static pfunc *p = &__init_array_start[0];

    cyg_hal_stop_constructors = 0;
    for (; p < __init_array_end; p++) {
        (*p) ();
        if (cyg_hal_stop_constructors) {
            p++;
            break;
        }
    }
#else
    pfunc *p;

    for (p = &__init_array_start[0]; p < __init_array_end; p++)
        (*p) ();
#endif

} // cyg_hal_invoke_constructors()


void hal_interrupt_mask(int vector)
{
    cyg_uint32 tmp = (cyg_uint32) (1<<vector);
    asm volatile(
            "csrc  mie, %0\n"
            :
            :"r"(tmp)
            );
}

void hal_interrupt_unmask(int vector)
{
    cyg_uint32 tmp = (cyg_uint32) (1<<vector);
    asm volatile(
            "csrs   mie, %0\n"
            :
            :"r"(tmp)
            );
}

void hal_interrupt_acknowledge(int vector)
{
}

void hal_interrupt_configure(int vector, int level, int up)
{
}

void hal_interrupt_set_level(int vector, int level)
{
}

// TRAP HADLER and consequenses
typedef void* Cyg_Interrupt;

void interrupt_end(
    cyg_uint32          isr_ret,
    Cyg_Interrupt       *intr,
    HAL_SavedRegisters  *ctx
    );

//void cyg_interrupt_call_pending_DSRs(void);

cyg_uint32 trap_handler_diag(cyg_uint32 mcause, HAL_SavedRegisters *regs)
{
    diag_printf("In trap_handler, mcause %X\n", mcause);
    /*cyg_uint32 isr_answer;
    cyg_uint32 (*isr)(cyg_uint32,void*);
//check cause and jump to accompanying vector
    if(mcause == CYGNUM_HAL_MTIMER_CAUSE) {

        //TODO: must be removed after debugging
        asm volatile ("csrw mtimecmp, 0x0\n"
                       :
                       :
                        );

        isr = hal_interrupt_handlers[CYGNUM_HAL_MTIMER_INTERRUPT];
        isr_answer = isr(CYGNUM_HAL_MTIMER_INTERRUPT,
                hal_interrupt_data[CYGNUM_HAL_MTIMER_INTERRUPT]);

        interrupt_end(isr_answer, hal_interrupt_objects[CYGNUM_HAL_MTIMER_INTERRUPT], regs);

    } else {
        while(1);
    }*/
    return mcause;
}

cyg_uint32 hal_default_isr(CYG_ADDRWORD vector, CYG_ADDRWORD data)
{
    return 0;
}

//==========================================================================
// When compiling C++ code with static objects the compiler
// inserts a call to __cxa_atexit() with __dso_handle as one of the
// arguments. __cxa_atexit() would normally be provided by glibc, and
// __dso_handle is part of crtstuff.c. eCos applications
// are linked rather differently, so either a differently-configured
// compiler is needed or dummy versions of these symbols should be
// provided. If these symbols are not actually used then providing
// them is still harmless, linker garbage collection will remove them.

void
__cxa_atexit(void (*arg1)(void*), void* arg2, void* arg3)
{
}

void*   __dso_handle = (void*) &__dso_handle;
