# eCos makefile

# This is a generated file - do not edit

export PREFIX := /home/grihey/src/ecos/ecos-3.0/Configs/untitled_install
export COMMAND_PREFIX := sh-elf-
export CC := $(COMMAND_PREFIX)gcc
export OBJCOPY := $(COMMAND_PREFIX)objcopy
export HOST := UNIX
export AR := $(COMMAND_PREFIX)ar

export REPOSITORY := /home/grihey/LAB/ecos/packages
PACKAGE := hal/sh/sh4/current
OBJECT_PREFIX := hal_sh_sh4
CFLAGS := -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Woverloaded-virtual -Wno-write-strings -ml -m3 -ggdb -O2 -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions
LDFLAGS := -ml -m3 -ggdb -nostdlib -Wl,--gc-sections -Wl,-static
VPATH := $(REPOSITORY)/$(PACKAGE)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(PREFIX)/include $(foreach dir,$(VPATH),-I$(dir) -I$(dir)/src -I$(dir)/tests) -I.
MLT := $(wildcard $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.ldi $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.h)
TESTS := 

build: headers libtarget.a.stamp

LIBRARY := libtarget.a
COMPILE := src/sh4_scif.c src/var_misc.c src/variant.S
OBJECTS := $(COMPILE:.cxx=.o.d)
OBJECTS := $(OBJECTS:.cpp=.o.d)
OBJECTS := $(OBJECTS:.c=.o.d)
OBJECTS := $(OBJECTS:.S=.o.d)

$(LIBRARY).stamp: $(OBJECTS)
	$(AR) rcs $(PREFIX)/lib/$(@:.stamp=) $(foreach obj,$?,$(if $(obj:%.o=),$(dir $(obj))$(OBJECT_PREFIX)_$(notdir $(obj:.o.d=.o)),$(obj)))
	@cat $(foreach obj,$^,$(obj:.o=.o.d)) > $(@:.stamp=.deps)
	@touch $@

$(PREFIX)/include/cyg/hal/sh4_offsets.inc: $(wildcard $(REPOSITORY)/$(PACKAGE)/src/var_mk_defs.c)
	$(CC) $(ACTUAL_CFLAGS) $(INCLUDE_PATH) -Wp,-MD,sh4_offsets.tmp -o var_mk_defs.tmp -S $<
	fgrep .equ var_mk_defs.tmp | sed s/#// > $@
	@echo $@ ": \\" > $(notdir $@).deps
	@tail -n +2 sh4_offsets.tmp >> $(notdir $@).deps
	@echo >> $(notdir $@).deps
	@rm sh4_offsets.tmp var_mk_defs.tmp
	

headers: mlt_headers $(PREFIX)/include/cyg/hal/mod_regs_intc.h $(PREFIX)/include/cyg/hal/var_io.h $(PREFIX)/include/cyg/hal/mod_regs_cac.h $(PREFIX)/include/cyg/hal/var_cache.h $(PREFIX)/include/cyg/hal/variant.inc $(PREFIX)/include/cyg/hal/mod_regs_cpg.h $(PREFIX)/include/cyg/hal/mod_regs_rtc.h $(PREFIX)/include/cyg/hal/mod_regs_pfc.h $(PREFIX)/include/cyg/hal/mod_regs_dma.h $(PREFIX)/include/cyg/hal/mod_regs_bsc.h $(PREFIX)/include/cyg/hal/var_intr.h $(PREFIX)/include/cyg/hal/sh4_scif.h $(PREFIX)/include/cyg/hal/mod_regs_ser.h $(PREFIX)/include/cyg/hal/var_regs.h $(PREFIX)/include/cyg/hal/mod_regs_tmu.h $(PREFIX)/include/cyg/hal/mod_regs_mmu.h $(PREFIX)/include/cyg/hal/mod_7751.h $(PREFIX)/include/cyg/hal/mod_202.h $(PREFIX)/include/cyg/hal/mod_regs_emi.h $(PREFIX)/include/cyg/hal/mod_regs_ubc.h $(PREFIX)/include/cyg/hal/mod_7750.h $(PREFIX)/include/cyg/hal/mod_regs_pcic.h $(PREFIX)/include/cyg/hal/mod_regs_femi.h

$(PREFIX)/include/cyg/hal/mod_regs_intc.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_intc.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/var_io.h: $(REPOSITORY)/$(PACKAGE)/include/var_io.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_cac.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_cac.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/var_cache.h: $(REPOSITORY)/$(PACKAGE)/include/var_cache.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/variant.inc: $(REPOSITORY)/$(PACKAGE)/include/variant.inc
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_cpg.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_cpg.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_rtc.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_rtc.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_pfc.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_pfc.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_dma.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_dma.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_bsc.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_bsc.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/var_intr.h: $(REPOSITORY)/$(PACKAGE)/include/var_intr.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/sh4_scif.h: $(REPOSITORY)/$(PACKAGE)/include/sh4_scif.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_ser.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_ser.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/var_regs.h: $(REPOSITORY)/$(PACKAGE)/include/var_regs.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_tmu.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_tmu.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_mmu.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_mmu.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_7751.h: $(REPOSITORY)/$(PACKAGE)/include/mod_7751.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_202.h: $(REPOSITORY)/$(PACKAGE)/include/mod_202.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_emi.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_emi.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_ubc.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_ubc.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_7750.h: $(REPOSITORY)/$(PACKAGE)/include/mod_7750.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_pcic.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_pcic.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/mod_regs_femi.h: $(REPOSITORY)/$(PACKAGE)/include/mod_regs_femi.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

include $(REPOSITORY)/pkgconf/rules.mak

