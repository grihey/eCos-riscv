#ifndef CYGONCE_HAL_ARCH_INC
#define CYGONCE_HAL_ARCH_INC
##=============================================================================
##
##	arch.inc
##
##	MIPS assembler header file
##
##=============================================================================
## ####ECOSGPLCOPYRIGHTBEGIN####                                            
## -------------------------------------------                              
## This file is part of eCos, the Embedded Configurable Operating System.   
## Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
##
## eCos is free software; you can redistribute it and/or modify it under    
## the terms of the GNU General Public License as published by the Free     
## Software Foundation; either version 2 or (at your option) any later      
## version.                                                                 
##
## eCos is distributed in the hope that it will be useful, but WITHOUT      
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
## for more details.                                                        
##
## You should have received a copy of the GNU General Public License        
## along with eCos; if not, write to the Free Software Foundation, Inc.,    
## 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
##
## As a special exception, if other files instantiate templates or use      
## macros or inline functions from this file, or you compile this file      
## and link it with other works to produce a work based on this file,       
## this file does not by itself cause the resulting work to be covered by   
## the GNU General Public License. However the source code for this file    
## must still be made available in accordance with section (3) of the GNU   
## General Public License v2.                                               
##
## This exception does not invalidate any other reasons why a work based    
## on this file might be covered by the GNU General Public License.         
## -------------------------------------------                              
## ####ECOSGPLCOPYRIGHTEND####                                              
##=============================================================================
#######DESCRIPTIONBEGIN####
##
## Author(s): 	nickg
## Contributors:	nickg, dmoseley
## Date:	1997-10-16
## Purpose:	Architecture definitions.
## Description:	This file contains various definitions and macros that are
##              useful for writing assembly code for the MIPS CPU family.
## Usage:
##		#include <cyg/hal/arch.inc>
##		...
##		
##
######DESCRIPTIONEND####
##
##=============================================================================

//#include <cyg/hal/riscv.inc>
//#include <cyg/hal/variant.inc>

#define mips_regsize 	4

// related to HAL_SavedRegisters;
#define	mipsreg_regs	0
#ifdef CYGHWR_HAL_MIPS_FPU
# define mipsreg_fpureg	(mipsreg_reg+(mips_regsize*32))
# define mipsreg_mstatus (mipsreg_fpureg+(mips_regsize*32))
#else
# define mipsreg_mstatus (mipsreg_regs+(mips_regsize*32))
#endif
#define	mipsreg_pc	(mipsreg_mstatus+mips_regsize)
#define	mipsreg_mcause	(mipsreg_pc+mips_regsize)
#define	mipsreg_mbadaddr	(mipsreg_mcause+mips_regsize)
#define	mipsreg_size	(mipsreg_mbadaddr+mips_regsize)

# The following expression ensures that the decrement is always a
# multiple of 16 bytes. This is a requirement of the MEABI used in
# MIPS32/64 targets.
