#ifndef CYGONCE_HAL_HAL_INTR_H
#define CYGONCE_HAL_HAL_INTR_H

//==========================================================================
//
//      hal_intr.h
//
//      HAL Interrupt and clock support
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
// Purpose:      Define Interrupt support
// Description:  The macros defined here provide the HAL APIs for handling
//               interrupts and the clock.
//              
// Usage:
//              #include <cyg/hal/hal_intr.h>
//              ...
//              
//
//####DESCRIPTIONEND####
//
//==========================================================================

#include <pkgconf/hal.h>

#ifndef __ASSEMBLER__
#include <cyg/infra/cyg_type.h>
#endif //__ASSEMBLER__ 

//#include <cyg/hal/hal_io.h>

#include <cyg/hal/var_intr.h>


#define HAL_DEFAULT_ISR hal_default_isr

#define CYGNUM_HAL_VSR_MIN                   0
#define CYGNUM_HAL_VSR_MAX                  15

#ifndef __ASSEMBLER__

externC volatile CYG_ADDRESS    hal_interrupt_handlers[CYGNUM_HAL_ISR_COUNT];
externC volatile CYG_ADDRWORD   hal_interrupt_data[CYGNUM_HAL_ISR_COUNT];
externC volatile CYG_ADDRESS    hal_interrupt_objects[CYGNUM_HAL_ISR_COUNT];

externC cyg_uint32 hal_default_isr(CYG_ADDRWORD vector, CYG_ADDRWORD data);

// VSR table
externC volatile CYG_ADDRESS    hal_vsr_table[CYGNUM_HAL_VSR_MAX+1];

#ifndef CYGNUM_HAL_INTERRUPT_RTC
#define CYGNUM_HAL_INTERRUPT_RTC            CYGNUM_HAL_MTIMER_INTERRUPT 
#endif

#define HAL_DISABLE_INTERRUPTS(_old_)		    \
CYG_MACRO_START                                 \
    cyg_uint32 tmp = 0;        \
    __asm volatile 	(                           \
                "csrrci %0, mstatus, 1;"        \
                : "=r"(tmp)                     \
                :                               \
                );                              \
    _old_ = tmp;                                \
CYG_MACRO_END

#define HAL_ENABLE_INTERRUPTS()					\
CYG_MACRO_START                                 \
    __asm volatile 	( "csrs mstatus,1" )        \
CYG_MACRO_END

#define HAL_RESTORE_INTERRUPTS(_old_)           \
CYG_MACRO_START                                 \
    cyg_uint32 tmp = (cyg_uint32) _old_;        \
    asm volatile (                              \
            "csrw   mstatus, %0\n"              \
            :                                   \
            :"r"(tmp)                           \
            );                                  \
CYG_MACRO_END

#define HAL_CLOCK_INITIALIZE( _period_ )        \
CYG_MACRO_START                                 \
    cyg_uint32 tmp = (cyg_uint32) _period_;     \
    cyg_uint32 dest = 0;                        \
    cyg_uint32 mtime = 0;                       \
    asm volatile(                               \
            "csrr   %2, mtime\n"                \
            "add    %0, %2, %1\n"               \
            "csrw   mtimecmp, %0\n"             \
            :"=r"(dest)                         \
            :"r"(tmp),"r"(mtime)                \
            );                                  \
CYG_MACRO_END

#define HAL_CLOCK_RESET( _vector_, _period_ )   \
CYG_MACRO_START                                 \
    cyg_uint32 tmp = (cyg_uint32) _period_;     \
    cyg_uint32 dest = 0;                        \
    cyg_uint32 mtime = 0;                       \
    asm volatile(                               \
            "csrr   %2, mtime\n"                \
            "add    %0, %2, %1\n"               \
            "csrw   mtimecmp, %0\n"             \
            :"=r"(dest)                         \
            :"r"(tmp),"r"(mtime)                \
            );                                  \
CYG_MACRO_END

#define HAL_CLOCK_READ( _pvalue_ )              \
CYG_MACRO_START                                 \
    register cyg_uint32 tmp;                    \
    asm volatile(                               \
            "csrr   %0, mtime\n"                \
            :"=r"(tmp)                          \
            :                                   \
            );                                  \
    (*_pvalue_) = tmp;                          \
CYG_MACRO_END

#define CYGARC_HAL_SAVE_GP()                    \
    CYG_MACRO_START                             \
    register CYG_ADDRWORD __gp_save;            \
    asm volatile ( "mv   %0,x3;"                \
                   ".extern _gp;"               \
                   "la     x3,_gp;"             \
                     : "=r"(__gp_save))

#define CYGARC_HAL_RESTORE_GP()                 \
    asm volatile (                              \
            "move   x3,%0;"                     \
            :: "r"(__gp_save) );                \
    CYG_MACRO_END

#ifndef HAL_TRANSLATE_VECTOR
#define HAL_TRANSLATE_VECTOR(_vector_,_index_) \
    (_index_) = (_vector_)
#endif //HAL_TRANSLATE_VECTOR

#define HAL_INTERRUPT_ATTACH( _vector_, _isr_, _data_, _object_ )           \
CYG_MACRO_START                                                             \
    cyg_uint32 _index_;                                                     \
    HAL_TRANSLATE_VECTOR( _vector_, _index_ );                              \
                                                                            \
    if( hal_interrupt_handlers[_index_] == (CYG_ADDRESS)HAL_DEFAULT_ISR )   \
    {                                                                       \
        hal_interrupt_handlers[_index_] = (CYG_ADDRESS)_isr_;               \
        hal_interrupt_data[_index_] = (CYG_ADDRWORD)_data_;                 \
        hal_interrupt_objects[_index_] = (CYG_ADDRESS)_object_;             \
    }                                                                       \
CYG_MACRO_END

#define HAL_INTERRUPT_DETACH( _vector_, _isr_ )                         \
CYG_MACRO_START                                                         \
    cyg_uint32 _index_;                                                 \
    HAL_TRANSLATE_VECTOR( _vector_, _index_ );                          \
                                                                        \
    if( hal_interrupt_handlers[_index_] == (CYG_ADDRESS)_isr_ )         \
    {                                                                   \
        hal_interrupt_handlers[_index_] = (CYG_ADDRESS)HAL_DEFAULT_ISR; \
        hal_interrupt_data[_index_] = 0;                                \
        hal_interrupt_objects[_index_] = 0;                             \
    }                                                                   \
CYG_MACRO_END

#define HAL_INTERRUPT_IN_USE( _vector_, _state_)                          \
CYG_MACRO_START                                                           \
    cyg_uint32 _index_;                                                   \
    HAL_TRANSLATE_VECTOR ((_vector_), _index_);                           \
                                                                          \
    if( hal_interrupt_handlers[_index_] == (CYG_ADDRESS)HAL_DEFAULT_ISR ) \
        (_state_) = 0;                                                    \
    else                                                                  \
        (_state_) = 1;                                                    \
CYG_MACRO_END

#define HAL_VSR_GET( _vector_, _pvsr_ )                                   \
    *(_pvsr_) = (void (*)())hal_vsr_table[_vector_];
    

#define HAL_VSR_SET( _vector_, _vsr_, _poldvsr_ ) CYG_MACRO_START         \
    if( (void*)_poldvsr_ != NULL)                                         \
        *(CYG_ADDRESS *)_poldvsr_ = (CYG_ADDRESS)hal_vsr_table[_vector_]; \
    hal_vsr_table[_vector_] = (CYG_ADDRESS)_vsr_;                         \
CYG_MACRO_END

// Causes numbers
// #define
// #define
// #define

externC void hal_interrupt_mask(int);
externC void hal_interrupt_unmask(int);
externC void hal_interrupt_acknowledge(int);
externC void hal_interrupt_configure(int, int, int);
externC void hal_interrupt_set_level(int, int);

#define HAL_INTERRUPT_MASK( _vector_ )                     \
    hal_interrupt_mask( _vector_ ) 
#define HAL_INTERRUPT_UNMASK( _vector_ )                   \
    hal_interrupt_unmask( _vector_ )
#define HAL_INTERRUPT_ACKNOWLEDGE( _vector_ )              \
    hal_interrupt_acknowledge( _vector_ )
#define HAL_INTERRUPT_CONFIGURE( _vector_, _level_, _up_ ) \
    hal_interrupt_configure( _vector_, _level_, _up_ )
#define HAL_INTERRUPT_SET_LEVEL( _vector_, _level_ )       \
    hal_interrupt_set_level( _vector_, _level_ )

typedef cyg_uint32 CYG_INTERRUPT_STATE;
#endif // __ASSEMBLER__

//--------------------------------------------------------------------------
#endif // ifndef CYGONCE_HAL_HAL_INTR_H
// End of hal_intr.h
