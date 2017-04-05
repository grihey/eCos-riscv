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
## Author(s):       grihey
## Contributors:	
## Date:	        2017-03-22
## Purpose:	Architecture definitions.
## Description:	This file contains various definitions and macros that are
##              useful for writing assembly code for the RISCV CPU family.
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

#ifdef CYGHWR_HAL_RISCV_64BIT
# define riscv_regsize 	8
# define STORE  sd
# define LOAD   ld
#else
# define riscv_regsize 	4
# define STORE  sw
# define LOAD   lw
#endif //CYGHWR_HAL_RISCV_64BIT

#ifdef CYGHWR_HAL_RISCV_FPU_64BIT
# define riscv_fpuregsize 	8
# define STOREF    fsd 
# define LOADF     fld 
#else
# define riscv_fpuregsize 	4
# define STOREF    fsw
# define LOADF     flw
#endif //CYGHWR_HAL_RISCV_FPU_64BIT

// related to HAL_SavedRegisters;
#define	riscvreg_regs	0
#ifdef CYGHWR_HAL_MIPS_FPU
# define riscvreg_fpureg	    (riscvreg_reg+(riscv_regsize*32))
# define riscvreg_mstatus    (riscvreg_fpureg+(riscv_fpuregsize*32))
#else
# define riscvreg_mstatus    (riscvreg_regs+(riscv_regsize*32))
#endif
#define riscvreg_mepc        (riscvreg_mstatus+riscv_regsize)
#define	riscvreg_size	    (riscvreg_mepc+riscv_regsize)

/* 
.altmacro
.macro hal_fpu_save_regs base:req

    STOREF      f0,  (0  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f1,  (1  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f2,  (2  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f3,  (3  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f4,  (4  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f5,  (5  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f6,  (6  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f7,  (7  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f8,  (8  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f9,  (9  * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f10, (10 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f11, (11 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f12, (12 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f13, (13 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f14, (14 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f15, (15 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f16, (16 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f17, (17 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f18, (18 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f19, (19 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f20, (20 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f21, (21 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f22, (22 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f23, (23 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f24, (24 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f25, (25 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f26, (26 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f27, (27 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f28, (28 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f29, (29 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f30, (30 * riscv_regsize)+riscvreg_fpureg(\base)
    STOREF      f31, (31 * riscv_regsize)+riscvreg_fpureg(\base)
    
.endm

.macro hal_fpu_load_regs base:req
    LOADF       f0,  (0  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f1,  (1  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f2,  (2  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f3,  (3  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f4,  (4  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f5,  (5  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f6,  (6  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f7,  (7  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f8,  (8  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f9,  (9  * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f10, (10 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f11, (11 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f12, (12 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f13, (13 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f14, (14 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f15, (15 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f16, (16 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f17, (17 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f18, (18 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f19, (19 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f20, (20 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f21, (21 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f22, (22 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f23, (23 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f24, (24 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f25, (25 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f26, (26 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f27, (27 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f28, (28 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f29, (29 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f30, (30 * riscv_regsize)+riscvreg_fpureg(\base)
    LOADF       f31, (31 * riscv_regsize)+riscvreg_fpureg(\base)
.endm */

#endif //CYGONCE_HAL_ARCH_INC
