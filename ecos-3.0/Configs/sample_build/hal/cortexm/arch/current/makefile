# eCos makefile

# This is a generated file - do not edit

export PREFIX := /home/grihey/src/ecos/ecos-3.0/Configs/sample_install
export COMMAND_PREFIX := arm-eabi-
export CC := $(COMMAND_PREFIX)gcc
export OBJCOPY := $(COMMAND_PREFIX)objcopy
export HOST := UNIX
export AR := $(COMMAND_PREFIX)ar

export REPOSITORY := /home/grihey/LAB/ecos/packages
PACKAGE := hal/cortexm/arch/current
OBJECT_PREFIX := hal_cortexm_arch
CFLAGS := -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Woverloaded-virtual -Wno-write-strings -mcpu=cortex-m3 -mthumb -g -O2 -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions
LDFLAGS := -mcpu=cortex-m3 -mthumb -Wl,--gc-sections -Wl,-static -Wl,-n -g -nostdlib
VPATH := $(REPOSITORY)/$(PACKAGE)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(PREFIX)/include $(foreach dir,$(VPATH),-I$(dir) -I$(dir)/src -I$(dir)/tests) -I.
MLT := $(wildcard $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.ldi $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.h)
TESTS := 

build: headers libtarget.a.stamp

LIBRARY := libtarget.a
COMPILE := src/hal_misc.c src/context.S src/cortexm_stub.c
OBJECTS := $(COMPILE:.cxx=.o.d)
OBJECTS := $(OBJECTS:.cpp=.o.d)
OBJECTS := $(OBJECTS:.c=.o.d)
OBJECTS := $(OBJECTS:.S=.o.d)

$(LIBRARY).stamp: $(OBJECTS)
	$(AR) rcs $(PREFIX)/lib/$(@:.stamp=) $(foreach obj,$?,$(if $(obj:%.o=),$(dir $(obj))$(OBJECT_PREFIX)_$(notdir $(obj:.o.d=.o)),$(obj)))
	@cat $(foreach obj,$^,$(obj:.o=.o.d)) > $(@:.stamp=.deps)
	@touch $@

$(PREFIX)/lib/vectors.o: $(wildcard $(REPOSITORY)/$(PACKAGE)/src/vectors.S)
	$(CC) -Wp,-MD,vectors.tmp $(INCLUDE_PATH) $(CFLAGS) -c -o $@ $<
	@echo $@ ": \\" > $(notdir $@).deps
	@tail -n +2 vectors.tmp >> $(notdir $@).deps
	@echo >> $(notdir $@).deps
	@rm vectors.tmp
	

$(PREFIX)/lib/target.ld: $(wildcard $(REPOSITORY)/$(PACKAGE)/src/cortexm.ld)
	$(CC) -E -P -Wp,-MD,target.tmp -xc $(INCLUDE_PATH) $(ACTUAL_CFLAGS) -o $@ $<
	@echo $@ ": \\" > $(notdir $@).deps
	@tail -n +2 target.tmp >> $(notdir $@).deps
	@echo >> $(notdir $@).deps
	@rm target.tmp
	

headers: mlt_headers $(PREFIX)/include/cyg/hal/hal_arch.h $(PREFIX)/include/cyg/hal/hal_intr.h $(PREFIX)/include/cyg/hal/cortexm_stub.h $(PREFIX)/include/cyg/hal/fpv4_sp_d16_libm.h $(PREFIX)/include/cyg/hal/hal_arch.inc $(PREFIX)/include/cyg/hal/fpv4_sp_d16.h $(PREFIX)/include/cyg/hal/basetype.h $(PREFIX)/include/cyg/hal/cortexm_regs.h $(PREFIX)/include/cyg/hal/hal_io.h $(PREFIX)/include/cyg/hal/cortexm_endian.h $(PREFIX)/include/cyg/hal/cortexm_core.h $(PREFIX)/include/cyg/hal/cortexm_fpu.h

$(PREFIX)/include/cyg/hal/hal_arch.h: $(REPOSITORY)/$(PACKAGE)/include/hal_arch.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_intr.h: $(REPOSITORY)/$(PACKAGE)/include/hal_intr.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/cortexm_stub.h: $(REPOSITORY)/$(PACKAGE)/include/cortexm_stub.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/fpv4_sp_d16_libm.h: $(REPOSITORY)/$(PACKAGE)/include/fpv4_sp_d16_libm.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_arch.inc: $(REPOSITORY)/$(PACKAGE)/include/hal_arch.inc
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/fpv4_sp_d16.h: $(REPOSITORY)/$(PACKAGE)/include/fpv4_sp_d16.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/basetype.h: $(REPOSITORY)/$(PACKAGE)/include/basetype.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/cortexm_regs.h: $(REPOSITORY)/$(PACKAGE)/include/cortexm_regs.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_io.h: $(REPOSITORY)/$(PACKAGE)/include/hal_io.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/cortexm_endian.h: $(REPOSITORY)/$(PACKAGE)/include/cortexm_endian.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/cortexm_core.h: $(REPOSITORY)/$(PACKAGE)/include/cortexm_core.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/cortexm_fpu.h: $(REPOSITORY)/$(PACKAGE)/include/cortexm_fpu.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

include $(REPOSITORY)/pkgconf/rules.mak

