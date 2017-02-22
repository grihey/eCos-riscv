# eCos makefile

# This is a generated file - do not edit

export HOST := UNIX
export PREFIX := /home/grihey/src/ecos/ecos-3.0/Configs/sample_install
export COMMAND_PREFIX := arm-eabi-
export CC := $(COMMAND_PREFIX)gcc
export OBJCOPY := $(COMMAND_PREFIX)objcopy
export AR := $(COMMAND_PREFIX)ar

.PHONY: default build clean tests headers

build: headers $(PREFIX)/include/pkgconf/ecos.mak
	$(MAKE) -r -C services/memalloc/common/current heapgeninc.tcl
	$(MAKE) -r -C services/memalloc/common/current heaps.cxx
	$(MAKE) -r -C hal/cortexm/arch/current $@
	$(MAKE) -r -C hal/cortexm/stm32/var/current $@
	$(MAKE) -r -C hal/cortexm/stm32/stm3210e_eval/current $@
	$(MAKE) -r -C io/spi/current $@
	$(MAKE) -r -C devs/spi/cortexm/stm32/current $@
	$(MAKE) -r -C io/usb/common/current $@
	$(MAKE) -r -C devs/usb/cortexm/stm32/current $@
	$(MAKE) -r -C hal/common/current $@
	$(MAKE) -r -C io/common/current $@
	$(MAKE) -r -C io/serial/current $@
	$(MAKE) -r -C infra/current $@
	$(MAKE) -r -C kernel/current $@
	$(MAKE) -r -C error/current $@
	$(MAKE) -r -C services/memalloc/common/current $@
	$(MAKE) -r -C language/c/libc/string/current $@
	$(MAKE) -r -C isoinfra/current $@
	$(MAKE) -r -C hal/common/current $(PREFIX)/lib/extras.o
	$(MAKE) -r -C hal/cortexm/arch/current $(PREFIX)/lib/vectors.o
	$(MAKE) -r -C hal/cortexm/arch/current $(PREFIX)/lib/target.ld
	@echo $@ finished

clean:
	$(MAKE) -r -C hal/cortexm/arch/current $@
	$(MAKE) -r -C hal/cortexm/stm32/var/current $@
	$(MAKE) -r -C hal/cortexm/stm32/stm3210e_eval/current $@
	$(MAKE) -r -C io/spi/current $@
	$(MAKE) -r -C devs/spi/cortexm/stm32/current $@
	$(MAKE) -r -C io/usb/common/current $@
	$(MAKE) -r -C devs/usb/cortexm/stm32/current $@
	$(MAKE) -r -C hal/common/current $@
	$(MAKE) -r -C io/common/current $@
	$(MAKE) -r -C io/serial/current $@
	$(MAKE) -r -C infra/current $@
	$(MAKE) -r -C kernel/current $@
	$(MAKE) -r -C error/current $@
	$(MAKE) -r -C services/memalloc/common/current $@
	$(MAKE) -r -C language/c/libc/string/current $@
	$(MAKE) -r -C isoinfra/current $@
	@echo $@ finished

tests: build
	$(MAKE) -r -C hal/cortexm/arch/current $@
	$(MAKE) -r -C hal/cortexm/stm32/var/current $@
	$(MAKE) -r -C hal/cortexm/stm32/stm3210e_eval/current $@
	$(MAKE) -r -C io/spi/current $@
	$(MAKE) -r -C devs/spi/cortexm/stm32/current $@
	$(MAKE) -r -C io/usb/common/current $@
	$(MAKE) -r -C devs/usb/cortexm/stm32/current $@
	$(MAKE) -r -C hal/common/current $@
	$(MAKE) -r -C io/common/current $@
	$(MAKE) -r -C io/serial/current $@
	$(MAKE) -r -C infra/current $@
	$(MAKE) -r -C kernel/current $@
	$(MAKE) -r -C error/current $@
	$(MAKE) -r -C services/memalloc/common/current $@
	$(MAKE) -r -C language/c/libc/string/current $@
	$(MAKE) -r -C isoinfra/current $@
	@echo $@ finished

headers:
	$(MAKE) -r -C hal/cortexm/arch/current $@
	$(MAKE) -r -C hal/cortexm/stm32/var/current $@
	$(MAKE) -r -C hal/cortexm/stm32/stm3210e_eval/current $@
	$(MAKE) -r -C io/spi/current $@
	$(MAKE) -r -C devs/spi/cortexm/stm32/current $@
	$(MAKE) -r -C io/usb/common/current $@
	$(MAKE) -r -C devs/usb/cortexm/stm32/current $@
	$(MAKE) -r -C hal/common/current $@
	$(MAKE) -r -C io/common/current $@
	$(MAKE) -r -C io/serial/current $@
	$(MAKE) -r -C infra/current $@
	$(MAKE) -r -C kernel/current $@
	$(MAKE) -r -C error/current $@
	$(MAKE) -r -C services/memalloc/common/current $@
	$(MAKE) -r -C language/c/libc/string/current $@
	$(MAKE) -r -C isoinfra/current $@
	@echo $@ finished

$(PREFIX)/include/pkgconf/ecos.mak: makefile
	@echo 'ECOS_GLOBAL_CFLAGS = -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Woverloaded-virtual -Wno-write-strings -mcpu=cortex-m3 -mthumb -g -O2 -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions' > $@
	@echo 'ECOS_GLOBAL_LDFLAGS = -mcpu=cortex-m3 -mthumb -Wl,--gc-sections -Wl,-static -Wl,-n -g -nostdlib' >> $@
	@echo 'ECOS_COMMAND_PREFIX = $(COMMAND_PREFIX)' >> $@

