# eCos makefile

# This is a generated file - do not edit

export PREFIX := /home/grihey/src/ecos/ecos-3.0/Configs/untitled_install
export COMMAND_PREFIX := sh-elf-
export CC := $(COMMAND_PREFIX)gcc
export OBJCOPY := $(COMMAND_PREFIX)objcopy
export HOST := UNIX
export AR := $(COMMAND_PREFIX)ar

export REPOSITORY := /home/grihey/LAB/ecos/packages
PACKAGE := hal/sh/arch/current
OBJECT_PREFIX := hal_sh_arch
CFLAGS := -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Woverloaded-virtual -Wno-write-strings -ml -m3 -ggdb -O2 -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions
LDFLAGS := -ml -m3 -ggdb -nostdlib -Wl,--gc-sections -Wl,-static
VPATH := $(REPOSITORY)/$(PACKAGE)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(PREFIX)/include $(foreach dir,$(VPATH),-I$(dir) -I$(dir)/src -I$(dir)/tests) -I.
MLT := $(wildcard $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.ldi $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.h)
TESTS := tests/intr0

build: headers libtarget.a.stamp

LIBRARY := libtarget.a
COMPILE := src/hal_misc.c src/context.S src/sh_stub.c
OBJECTS := $(COMPILE:.cxx=.o.d)
OBJECTS := $(OBJECTS:.cpp=.o.d)
OBJECTS := $(OBJECTS:.c=.o.d)
OBJECTS := $(OBJECTS:.S=.o.d)

$(LIBRARY).stamp: $(OBJECTS)
	$(AR) rcs $(PREFIX)/lib/$(@:.stamp=) $(foreach obj,$?,$(if $(obj:%.o=),$(dir $(obj))$(OBJECT_PREFIX)_$(notdir $(obj:.o.d=.o)),$(obj)))
	@cat $(foreach obj,$^,$(obj:.o=.o.d)) > $(@:.stamp=.deps)
	@touch $@

$(PREFIX)/include/cyg/hal/sh_offsets.inc: $(wildcard $(REPOSITORY)/$(PACKAGE)/src/hal_mk_defs.c)
	$(CC) $(ACTUAL_CFLAGS) $(INCLUDE_PATH) -Wp,-MD,sh_offsets.tmp -o hal_mk_defs.tmp -S $<
	fgrep .equ hal_mk_defs.tmp | sed s/#// > $@
	@echo $@ ": \\" > $(notdir $@).deps
	@tail -n +2 sh_offsets.tmp >> $(notdir $@).deps
	@echo >> $(notdir $@).deps
	@rm sh_offsets.tmp hal_mk_defs.tmp
	

$(PREFIX)/lib/vectors.o: $(wildcard $(REPOSITORY)/$(PACKAGE)/src/vectors.S)
	$(CC) -Wp,-MD,vectors.tmp $(INCLUDE_PATH) $(CFLAGS) -c -o $@ $<
	@echo $@ ": \\" > $(notdir $@).deps
	@tail -n +2 vectors.tmp >> $(notdir $@).deps
	@echo >> $(notdir $@).deps
	@rm vectors.tmp
	

$(PREFIX)/lib/target.ld: $(wildcard $(REPOSITORY)/$(PACKAGE)/src/sh.ld)
	$(CC) -E -P -Wp,-MD,target.tmp -xc $(INCLUDE_PATH) $(ACTUAL_CFLAGS) -o $@ $<
	@echo $@ ": \\" > $(notdir $@).deps
	@tail -n +2 target.tmp >> $(notdir $@).deps
	@echo >> $(notdir $@).deps
	@rm target.tmp
	

headers: mlt_headers $(PREFIX)/include/cyg/hal/hal_var_sp.h $(PREFIX)/include/cyg/hal/hal_var_bank.h $(PREFIX)/include/cyg/hal/sh_stub.h $(PREFIX)/include/cyg/hal/hal_arch.h $(PREFIX)/include/cyg/hal/arch.inc $(PREFIX)/include/cyg/hal/hal_intr_excevt.h $(PREFIX)/include/cyg/hal/hal_intr.h $(PREFIX)/include/cyg/hal/sh_regs.h $(PREFIX)/include/cyg/hal/basetype.h $(PREFIX)/include/cyg/hal/hal_var_bank.inc $(PREFIX)/include/cyg/hal/hal_intr_vecs.h $(PREFIX)/include/cyg/hal/hal_io.h $(PREFIX)/include/cyg/hal/hal_cache.h $(PREFIX)/include/cyg/hal/hal_var_sp.inc

$(PREFIX)/include/cyg/hal/hal_var_sp.h: $(REPOSITORY)/$(PACKAGE)/include/hal_var_sp.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_var_bank.h: $(REPOSITORY)/$(PACKAGE)/include/hal_var_bank.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/sh_stub.h: $(REPOSITORY)/$(PACKAGE)/include/sh_stub.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_arch.h: $(REPOSITORY)/$(PACKAGE)/include/hal_arch.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/arch.inc: $(REPOSITORY)/$(PACKAGE)/include/arch.inc
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_intr_excevt.h: $(REPOSITORY)/$(PACKAGE)/include/hal_intr_excevt.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_intr.h: $(REPOSITORY)/$(PACKAGE)/include/hal_intr.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/sh_regs.h: $(REPOSITORY)/$(PACKAGE)/include/sh_regs.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/basetype.h: $(REPOSITORY)/$(PACKAGE)/include/basetype.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_var_bank.inc: $(REPOSITORY)/$(PACKAGE)/include/hal_var_bank.inc
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_intr_vecs.h: $(REPOSITORY)/$(PACKAGE)/include/hal_intr_vecs.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_io.h: $(REPOSITORY)/$(PACKAGE)/include/hal_io.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_cache.h: $(REPOSITORY)/$(PACKAGE)/include/hal_cache.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_var_sp.inc: $(REPOSITORY)/$(PACKAGE)/include/hal_var_sp.inc
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

include $(REPOSITORY)/pkgconf/rules.mak

