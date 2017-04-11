// MLT linker script for MIPS32
//
//===========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002, 2005 Free Software Foundation, Inc.
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
//===========================================================================

#include <pkgconf/system.h>

OUTPUT_ARCH("riscv")

ENTRY(reset_vector)
#ifdef EXTRAS
INPUT(extras.o)
#endif
#if (__GNUC__ >= 3)
GROUP(libtarget.a libgcc.a libsupc++.a)
#else
GROUP(libtarget.a libgcc.a)
#endif

#define ALIGN_LMA 0x40
#define FOLLOWING(_section_) AT ((LOADADDR (_section_) + SIZEOF (_section_) + ALIGN_LMA - 1) & ~ (ALIGN_LMA - 1))
#define LMA_EQ_VMA
#define FORCE_OUTPUT . = .

#define SECTIONS_BEGIN

#if defined(CYG_HAL_STARTUP_RAM)

/* this version for RAM startup */
#define SECTION_fixed_vectors(_region_, _vma_, _lma_) \
    .rom_vectors _vma_ : _lma_ \
    { KEEP (*(.fixed_vectors)) \
    . = ALIGN(0x100);  } \
    > _region_

#define SECTION_rom_vectors(_region_, _vma_, _lma_) \
    .rom_vectors _vma_ : _lma_ \
    { KEEP (*(.trap_vectors)) \
    . = ALIGN(0x100); KEEP(*(.reset_vector)) } \
    > _region_

#elif defined(CYG_HAL_STARTUP_ROM)

/* this version for ROM startup */
#define SECTION_rom_vectors(_region_, _vma_, _lma_) \
    .rom_vectors _vma_ : _lma_ \
    { KEEP (*(.trap_vectors)) \
    . = ALIGN(0x100); KEEP(*(.reset_vector)) } \
    > _region_

#endif /* ROM startup version of ROM vectors */

#define SECTION_ROMISC(_region_, _vma_, _lma_)                                 \
  .interp _vma_  : _lma_ { *(.interp)                            } > _region_  \
  .hash          : FOLLOWING(.interp)        { *(.hash)          } > _region_  \
  .dynsym        : FOLLOWING(.hash)          { *(.dynsym)        } > _region_  \
  .dynstr        : FOLLOWING(.dynsym)        { *(.dynstr)        } > _region_  \
  .gnu.version   : FOLLOWING(.dynstr)        { *(.gnu.version)   } > _region_  \
  .gnu.version_d : FOLLOWING(.gnu.version)   { *(.gnu.version_d) } > _region_  \
  .gnu.version_r : FOLLOWING(.gnu.version_d) { *(.gnu.version_r) } > _region_  \
  .plt           : FOLLOWING(.gnu.version_r) { *(.plt)           } > _region_

#define SECTION_RELOCS(_region_, _vma_, _lma_)                              \
  .rel.text      :                                                          \
    {                                                                       \
      *(.rel.text)                                                          \
      *(.rel.text.*)                                                        \
      *(.rel.gnu.linkonce.t*)                                               \
    } > _region_                                                            \
  .rela.text     :                                                          \
    {                                                                       \
      *(.rela.text)                                                         \
      *(.rela.text.*)                                                       \
      *(.rela.gnu.linkonce.t*)                                              \
    } > _region_                                                            \
  .rel.data      :                                                          \
    {                                                                       \
      *(.rel.data)                                                          \
      *(.rel.data.*)                                                        \
      *(.rel.gnu.linkonce.d*)                                               \
    } > _region_                                                            \
  .rela.data     :                                                          \
    {                                                                       \
      *(.rela.data)                                                         \
      *(.rela.data.*)                                                       \
      *(.rela.gnu.linkonce.d*)                                              \
    } > _region_                                                            \
  .rel.rodata    :                                                          \
    {                                                                       \
      *(.rel.rodata)                                                        \
      *(.rel.rodata.*)                                                      \
      *(.rel.gnu.linkonce.r*)                                               \
    } > _region_                                                            \
  .rela.rodata   :                                                          \
    {                                                                       \
      *(.rela.rodata)                                                       \
      *(.rela.rodata.*)                                                     \
      *(.rela.gnu.linkonce.r*)                                              \
    } > _region_                                                            \
  .rel.got       :   { *(.rel.got)    } > _region_                          \
  .rela.got      :   { *(.rela.got)   } > _region_                          \
  .rel.ctors     :   { *(.rel.ctors)  } > _region_                          \
  .rela.ctors    :   { *(.rela.ctors) } > _region_                          \
  .rel.dtors     :   { *(.rel.dtors)  } > _region_                          \
  .rela.dtors    :   { *(.rela.dtors) } > _region_                          \
  .rel.init      :   { *(.rel.init)   } > _region_                          \
  .rela.init     :   { *(.rela.init)  } > _region_                          \
  .rel.fini      :   { *(.rel.fini)   } > _region_                          \
  .rela.fini     :   { *(.rela.fini)  } > _region_                          \
  .rel.bss       :   { *(.rel.bss)    } > _region_                          \
  .rela.bss      :   { *(.rela.bss)   } > _region_                          \
  .rel.plt       :   { *(.rel.plt)    } > _region_                          \
  .rela.plt      :   { *(.rela.plt)   } > _region_                          \
  .rel.dyn       :   { *(.rel.dyn)    } > _region_

#define SECTION_init(_region_, _vma_, _lma_)   \
  .init _vma_ : _lma_                          \
    {                                          \
      FORCE_OUTPUT; KEEP (*(.init))            \
    } > _region_ =0                            \
    _gp = ALIGN(16) + 0x7ff0;                     

#define SECTION_text(_region_, _vma_, _lma_)   \
  .text _vma_ : _lma_                          \
    {                                          \
      _stext = .; _ftext = . ;                 \
      *(.text)                                 \
      *(.text.*)                               \
      *(.gnu.warning)                          \
      *(.gnu.linkonce.t*)                      \
    } > _region_ =0                            \
  _etext = .; PROVIDE (etext = .);

#define SECTION_rodata(_region_, _vma_, _lma_)        \
  .rodata _vma_ : _lma_                               \
    {                                                 \
      FORCE_OUTPUT; *(.rodata) *(.rodata.*) *(.gnu.linkonce.r*)    \
    } > _region_

#define SECTION_data(_region_, _vma_, _lma_)          \
  .data _vma_ : _lma_                                 \
    {                                                 \
      __ram_data_start = ABSOLUTE (.); _fdata = . ;   \
      *(.data) *(.data.*) *(.gnu.linkonce.d*)         \
    . = ALIGN (8);                                    \
    SORT(CONSTRUCTORS)                                \
    } > _region_                                      \
    __rom_data_start = LOADADDR(.data);

#define SECTION_sdata(_region_, _vma_, _lma_)                 \
  .sdata _vma_ : _lma_                                        \
    {                                                         \
      FORCE_OUTPUT; *(.sdata) *(.sdata.*) *(.gnu.linkonce.s*) \
    } > _region_ \
  __ram_data_end = .; _edata = . ;              \
  PROVIDE (edata = .);

#define SECTION_sbss(_region_, _vma_, _lma_)                    \
  __bss_start = .; _fbss = .;                                   \
  .sbss _vma_ : _lma_                                           \
    {                                                           \
      FORCE_OUTPUT; *(.dynsbss) *(.sbss) *(.sbss.*) *(.scommon) \
    } > _region_

#define SECTION_bss(_region_, _vma_, _lma_)       \
  .bss _vma_ : _lma_                              \
    {                                             \
      __bss_start = .;                            \
      *(.dynbss) *(.bss) *(.bss.*) *(COMMON)      \
    } > _region_                                  \
  __bss_end = .;

/* The /DISCARD/ section ensures that the output will not contain a
 * .mdebug section as it confuses GDB. This is a workaround for CR 100804.
 */

#define SECTION_stack(_region_, _vma_, _lma_)     \
    .stack _vma_ : _lma_                          \
    {                                             \
        . = ALIGN(4);                             \
        _stack_end = .;                               \
        _stack = _stack_end + 0x800;             \
    } > _region_                    

#define SECTIONS_END . = ALIGN(4); _end = .; PROVIDE (end = .); \

#ifndef CYGPKG_HAL_MIPS_SIM
hal_virtual_vector_table = 0x0;
#endif

#include CYGHWR_MEMORY_LAYOUT_LDI
