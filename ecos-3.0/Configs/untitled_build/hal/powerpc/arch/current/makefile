# eCos makefile

# This is a generated file - do not edit

export PREFIX := /home/grihey/src/ecos/ecos-3.0/Configs/untitled_install
export COMMAND_PREFIX := powerpc-eabi-
export CC := $(COMMAND_PREFIX)gcc
export OBJCOPY := $(COMMAND_PREFIX)objcopy
export HOST := UNIX
export AR := $(COMMAND_PREFIX)ar

export REPOSITORY := /home/grihey/LAB/ecos/packages
PACKAGE := hal/powerpc/arch/current
OBJECT_PREFIX := hal_powerpc_arch
CFLAGS := -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Woverloaded-virtual -Wno-write-strings -mcpu=505 -g -O2 -ffunction-sections -fdata-sections -mmultiple -fno-rtti -fno-exceptions
LDFLAGS := -mcpu=505 -g -nostdlib -Wl,--gc-sections -Wl,-static
VPATH := $(REPOSITORY)/$(PACKAGE)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(PREFIX)/include $(foreach dir,$(VPATH),-I$(dir) -I$(dir)/src -I$(dir)/tests) -I.
MLT := $(wildcard $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.ldi $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.h)
TESTS := 

build: headers libtarget.a.stamp

LIBRARY := libtarget.a
COMPILE := src/hal_misc.c src/context.S src/ppc_stub.c src/hal_intr.c
OBJECTS := $(COMPILE:.cxx=.o.d)
OBJECTS := $(OBJECTS:.cpp=.o.d)
OBJECTS := $(OBJECTS:.c=.o.d)
OBJECTS := $(OBJECTS:.S=.o.d)

$(LIBRARY).stamp: $(OBJECTS)
	$(AR) rcs $(PREFIX)/lib/$(@:.stamp=) $(foreach obj,$?,$(if $(obj:%.o=),$(dir $(obj))$(OBJECT_PREFIX)_$(notdir $(obj:.o.d=.o)),$(obj)))
	@cat $(foreach obj,$^,$(obj:.o=.o.d)) > $(@:.stamp=.deps)
	@touch $@

$(PREFIX)/include/cyg/hal/ppc_offsets.inc: $(wildcard $(REPOSITORY)/$(PACKAGE)/src/hal_mk_defs.c)
	$(CC) $(ACTUAL_CFLAGS) $(INCLUDE_PATH) -Wp,-MD,ppc_offsets.tmp -o hal_mk_defs.tmp -S $<
	fgrep .equ hal_mk_defs.tmp | sed s/#// > $@
	@echo $@ ": \\" > $(notdir $@).deps
	@tail -n +2 ppc_offsets.tmp >> $(notdir $@).deps
	@echo >> $(notdir $@).deps
	@rm ppc_offsets.tmp hal_mk_defs.tmp
	

$(PREFIX)/lib/vectors.o: $(wildcard $(REPOSITORY)/$(PACKAGE)/src/vectors.S)
	$(CC) -Wp,-MD,vectors.tmp $(INCLUDE_PATH) $(CFLAGS) -c -o $@ $<
	@echo $@ ": \\" > $(notdir $@).deps
	@tail -n +2 vectors.tmp >> $(notdir $@).deps
	@echo >> $(notdir $@).deps
	@rm vectors.tmp
	

$(PREFIX)/lib/target.ld: $(wildcard $(REPOSITORY)/$(PACKAGE)/src/powerpc.ld)
	$(CC) -E -P -Wp,-MD,target.tmp -DEXTRAS=1 -xc $(INCLUDE_PATH) $(ACTUAL_CFLAGS) -o $@ $<
	@echo $@ ": \\" > $(notdir $@).deps
	@tail -n +2 target.tmp >> $(notdir $@).deps
	@echo >> $(notdir $@).deps
	@rm target.tmp
	

headers: mlt_headers $(PREFIX)/include/cyg/hal/hal_arch.h $(PREFIX)/include/cyg/hal/hal_mem.h $(PREFIX)/include/cyg/hal/arch.inc $(PREFIX)/include/cyg/hal/hal_intr.h $(PREFIX)/include/cyg/hal/redboot_linux_exec.h $(PREFIX)/include/cyg/hal/basetype.h $(PREFIX)/include/cyg/hal/ppc_regs.h $(PREFIX)/include/cyg/hal/hal_io.h $(PREFIX)/include/cyg/hal/hal_cache.h $(PREFIX)/include/cyg/hal/ppc_stub.h

$(PREFIX)/include/cyg/hal/hal_arch.h: $(REPOSITORY)/$(PACKAGE)/include/hal_arch.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_mem.h: $(REPOSITORY)/$(PACKAGE)/include/hal_mem.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/arch.inc: $(REPOSITORY)/$(PACKAGE)/include/arch.inc
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/hal_intr.h: $(REPOSITORY)/$(PACKAGE)/include/hal_intr.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/redboot_linux_exec.h: $(REPOSITORY)/$(PACKAGE)/include/redboot_linux_exec.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/basetype.h: $(REPOSITORY)/$(PACKAGE)/include/basetype.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/hal/ppc_regs.h: $(REPOSITORY)/$(PACKAGE)/include/ppc_regs.h
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

$(PREFIX)/include/cyg/hal/ppc_stub.h: $(REPOSITORY)/$(PACKAGE)/include/ppc_stub.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

include $(REPOSITORY)/pkgconf/rules.mak

