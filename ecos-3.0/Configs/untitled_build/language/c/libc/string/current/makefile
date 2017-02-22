# eCos makefile

# This is a generated file - do not edit

export PREFIX := /home/grihey/src/ecos/ecos-3.0/Configs/untitled_install
export COMMAND_PREFIX := frv-elf-
export CC := $(COMMAND_PREFIX)gcc
export OBJCOPY := $(COMMAND_PREFIX)objcopy
export HOST := UNIX
export AR := $(COMMAND_PREFIX)ar

export REPOSITORY := /home/grihey/LAB/ecos/packages
PACKAGE := language/c/libc/string/current
OBJECT_PREFIX := language_c_libc_string
CFLAGS := -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Woverloaded-virtual -Wno-write-strings -mcpu=fr400 -fPIC -G0 -g -O2 -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions
LDFLAGS := -mcpu=fr400 -fPIC -G0 -Wl,--gc-sections -Wl,-static -g -nostdlib
VPATH := $(REPOSITORY)/$(PACKAGE)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(PREFIX)/include $(foreach dir,$(VPATH),-I$(dir) -I$(dir)/src -I$(dir)/tests) -I.
MLT := $(wildcard $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.ldi $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.h)
TESTS := tests/memchr tests/memcmp1 tests/memcmp2 tests/memcpy1 tests/memcpy2 tests/memmove1 tests/memmove2 tests/memset tests/strcat1 tests/strcat2 tests/strchr tests/strcmp1 tests/strcmp2 tests/strcoll1 tests/strcoll2 tests/strcpy1 tests/strcpy2 tests/strcspn tests/strcspn tests/strlen tests/strncat1 tests/strncat2 tests/strncpy1 tests/strncpy2 tests/strpbrk tests/strrchr tests/strspn tests/strstr tests/strtok tests/strxfrm1 tests/strxfrm2 tests/strnlen

build: headers libtarget.a.stamp

LIBRARY := libtarget.a
COMPILE := src/memchr.cxx src/memcmp.cxx src/memmove.cxx src/strcat.cxx src/strchr.cxx src/strcmp.cxx src/strcoll.cxx src/strcpy.cxx src/strcspn.cxx src/strlen.cxx src/strncat.cxx src/strncmp.cxx src/strncpy.cxx src/strpbrk.cxx src/strrchr.cxx src/strspn.cxx src/strstr.cxx src/strsuppt.cxx src/strtok.cxx src/strxfrm.cxx src/bsdstring.cxx src/strdup.cxx src/strnlen.cxx
OBJECTS := $(COMPILE:.cxx=.o.d)
OBJECTS := $(OBJECTS:.cpp=.o.d)
OBJECTS := $(OBJECTS:.c=.o.d)
OBJECTS := $(OBJECTS:.S=.o.d)

$(LIBRARY).stamp: $(OBJECTS)
	$(AR) rcs $(PREFIX)/lib/$(@:.stamp=) $(foreach obj,$?,$(if $(obj:%.o=),$(dir $(obj))$(OBJECT_PREFIX)_$(notdir $(obj:.o.d=.o)),$(obj)))
	@cat $(foreach obj,$^,$(obj:.o=.o.d)) > $(@:.stamp=.deps)
	@touch $@

headers: mlt_headers $(PREFIX)/include/cyg/libc/string/bsdstring.h $(PREFIX)/include/cyg/libc/string/stringsupp.hxx $(PREFIX)/include/cyg/libc/string/string.inl $(PREFIX)/include/cyg/libc/string/string.h

$(PREFIX)/include/cyg/libc/string/bsdstring.h: $(REPOSITORY)/$(PACKAGE)/include/bsdstring.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/libc/string/stringsupp.hxx: $(REPOSITORY)/$(PACKAGE)/include/stringsupp.hxx
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/libc/string/string.inl: $(REPOSITORY)/$(PACKAGE)/include/string.inl
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/libc/string/string.h: $(REPOSITORY)/$(PACKAGE)/include/string.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

include $(REPOSITORY)/pkgconf/rules.mak

