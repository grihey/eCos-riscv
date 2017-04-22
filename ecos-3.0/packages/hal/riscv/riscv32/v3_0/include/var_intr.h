#ifndef CYGONCE_HAL_IMP_INTR_H
#define CYGONCE_HAL_IMP_INTR_H

//==========================================================================
//
//      imp_intr.h
//
//      MIPS32 Interrupt and clock support
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
// Author(s):    nickg
// Contributors: nickg, jskov,
//               gthomas, jlarmour, dmoseley
// Date:         1999-02-16
// Purpose:      MIPS32 Interrupt support
// Description:  The macros defined here provide the HAL APIs for handling
//               interrupts and the clock for variants of the MIPS32
//               architecture.
//              
// Usage:
//              #include <cyg/hal/imp_intr.h>
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

#include <cyg/hal/plf_intr.h>
 
#define CYGNUM_HAL_ISR_MIN      0
#define CYGNUM_HAL_ISR_MAX      7 
#define CYGNUM_HAL_ISR_COUNT    8

#ifdef CYGHWR_HAL_RISCV_RISCV32_CORE_SCR5
# define CYGNUM_HAL_MTIMER_INTERRUPT         7
# define CYGNUM_HAL_MTIMER_CAUSE             0x80000007 //priv spec 1.9
#endif
//--------------------------------------------------------------------------
#endif // ifndef CYGONCE_HAL_IMP_INTR_H
// End of imp_intr.h
