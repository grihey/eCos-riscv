# eCos makefile

# This is a generated file - do not edit

export PREFIX := /home/grihey/src/ecos/ecos-3.0/Configs/untitled_install
export COMMAND_PREFIX := frv-elf-
export CC := $(COMMAND_PREFIX)gcc
export OBJCOPY := $(COMMAND_PREFIX)objcopy
export HOST := UNIX
export AR := $(COMMAND_PREFIX)ar

export REPOSITORY := /home/grihey/LAB/ecos/packages
PACKAGE := infra/current
OBJECT_PREFIX := infra
CFLAGS := -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Woverloaded-virtual -Wno-write-strings -mcpu=fr400 -fPIC -G0 -g -O2 -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions
LDFLAGS := -mcpu=fr400 -fPIC -G0 -Wl,-static -g -nostdlib -Wl,--fatal-warnings
VPATH := $(REPOSITORY)/$(PACKAGE)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(PREFIX)/include $(foreach dir,$(VPATH),-I$(dir) -I$(dir)/src -I$(dir)/tests) -I.
MLT := $(wildcard $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.ldi $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.h)
TESTS := tests/cxxsupp tests/diag_sprintf1 tests/diag_sprintf2

build: headers libtarget.a.stamp

LIBRARY := libtarget.a
COMPILE := src/startup.cxx src/prestart.cxx src/pkgstart.cxx src/userstart.cxx src/dummyxxmain.cxx src/null.cxx src/simple.cxx src/fancy.cxx src/buffer.cxx src/diag.cxx src/tcdiag.cxx src/memcpy.c src/memset.c src/delete.cxx src/eprintf.c src/pure.cxx src/gccsupport.cxx
OBJECTS := $(COMPILE:.cxx=.o.d)
OBJECTS := $(OBJECTS:.cpp=.o.d)
OBJECTS := $(OBJECTS:.c=.o.d)
OBJECTS := $(OBJECTS:.S=.o.d)

$(LIBRARY).stamp: $(OBJECTS)
	$(AR) rcs $(PREFIX)/lib/$(@:.stamp=) $(foreach obj,$?,$(if $(obj:%.o=),$(dir $(obj))$(OBJECT_PREFIX)_$(notdir $(obj:.o.d=.o)),$(obj)))
	@cat $(foreach obj,$^,$(obj:.o=.o.d)) > $(@:.stamp=.deps)
	@touch $@

headers: mlt_headers $(PREFIX)/include/cyg/infra/clist.hxx $(PREFIX)/include/cyg/infra/cyg_type.inc $(PREFIX)/include/cyg/infra/cyg_trac.h $(PREFIX)/include/cyg/infra/diag.h $(PREFIX)/include/cyg/infra/testcase.h $(PREFIX)/include/cyg/infra/cyg_ass.h $(PREFIX)/include/cyg/infra/cyg_type.h

$(PREFIX)/include/cyg/infra/clist.hxx: $(REPOSITORY)/$(PACKAGE)/include/clist.hxx
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/infra/cyg_type.inc: $(REPOSITORY)/$(PACKAGE)/include/cyg_type.inc
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/infra/cyg_trac.h: $(REPOSITORY)/$(PACKAGE)/include/cyg_trac.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/infra/diag.h: $(REPOSITORY)/$(PACKAGE)/include/diag.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/infra/testcase.h: $(REPOSITORY)/$(PACKAGE)/include/testcase.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/infra/cyg_ass.h: $(REPOSITORY)/$(PACKAGE)/include/cyg_ass.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/infra/cyg_type.h: $(REPOSITORY)/$(PACKAGE)/include/cyg_type.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

include $(REPOSITORY)/pkgconf/rules.mak

