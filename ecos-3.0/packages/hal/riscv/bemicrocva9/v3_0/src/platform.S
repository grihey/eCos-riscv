##
#=============================================================================
##	platform.S
##
##	RISCV BeMicroCV-A9 platform code
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
## Author(s):	 grihey
## Contributors: grihey
## Date:	2017-03-17
## Purpose:	RISCV BeMicroCV-A9 platform code
## Description:	Platform specific code for BeMicroCV-A9 board.
##
##
##
##
######DESCRIPTIONEND####
##
##=============================================================================

#include <pkgconf/system.h>
#include <pkgconf/hal.h>

#ifdef CYGPKG_KERNEL
# include <pkgconf/kernel.h>
#endif

#include <cyg/hal/arch.inc>
#include <cyg/hal/hal_arch.h>
#include <cyg/hal/plf_defs.inc>

#include CYGBLD_HAL_PLATFORM_H

##-----------------------------------------------------------------------------

##-----------------------------------------------------------------------------
# Platform Initialization.
# This code performs platform specific initialization.

##-----------------------------------------------------------------------------
## I2C accessors - these need to delay after accessing the controller. 
// Need to delay between clocking the serial bits since the CPU is way too
// fast for the I2C interface. CPU runs at CYGHWR_HAL_MIPS_MALTA_CPU_CLOCK
// and the I2C no fasten than 1.7MHz. We want to delay the CPU for half
// an I2C cycle and two instructions are executed per loop, hence:
##-----------------------------------------------------------------------------

dummy_symbol:
    nop

## end of platform.S
