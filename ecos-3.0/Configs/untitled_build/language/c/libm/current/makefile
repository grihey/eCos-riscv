# eCos makefile

# This is a generated file - do not edit

export PREFIX := /home/grihey/src/ecos/ecos-3.0/Configs/untitled_install
export COMMAND_PREFIX := frv-elf-
export CC := $(COMMAND_PREFIX)gcc
export OBJCOPY := $(COMMAND_PREFIX)objcopy
export HOST := UNIX
export AR := $(COMMAND_PREFIX)ar

export REPOSITORY := /home/grihey/LAB/ecos/packages
PACKAGE := language/c/libm/current
OBJECT_PREFIX := language_c_libm
CFLAGS := -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Woverloaded-virtual -Wno-write-strings -mcpu=fr400 -fPIC -G0 -g -O2 -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fno-strict-aliasing
LDFLAGS := -mcpu=fr400 -fPIC -G0 -Wl,--gc-sections -Wl,-static -g -nostdlib
VPATH := $(REPOSITORY)/$(PACKAGE)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(PREFIX)/include $(foreach dir,$(VPATH),-I$(dir) -I$(dir)/src -I$(dir)/tests) -I.
MLT := $(wildcard $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.ldi $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.h)
TESTS := tests/vectors/acos tests/vectors/asin              tests/vectors/cos tests/vectors/cosh                         tests/vectors/sin tests/vectors/sinh                         tests/vectors/atan tests/vectors/atan2                       tests/vectors/tan tests/vectors/tanh                         tests/vectors/sqrt tests/vectors/pow                         tests/vectors/ceil tests/vectors/floor                       tests/vectors/fabs tests/vectors/fmod                        tests/vectors/frexp tests/vectors/ldexp                      tests/vectors/exp tests/vectors/log tests/vectors/log10       tests/vectors/acosf tests/vectors/asinf                      tests/vectors/cosf tests/vectors/coshf                       tests/vectors/sinf tests/vectors/sinhf                       tests/vectors/atanf tests/vectors/atan2f                     tests/vectors/tanf tests/vectors/tanhf                       tests/vectors/hypotf tests/vectors/sqrtf tests/vectors/powf  tests/vectors/floorf tests/vectors/ceilf                     tests/vectors/fabsf tests/vectors/fmodf                      tests/vectors/frexpf tests/vectors/ldexpf                    tests/vectors/expf tests/vectors/logf tests/vectors/log10f 

build: headers libtarget.a.stamp

LIBRARY := libtarget.a
COMPILE := src/misc/matherr.c src/misc/standard.c src/misc/standard_float.c src/misc/compatmode.cxx src/misc/infconst.c src/double/ieee754-core/e_acos.c src/double/ieee754-core/e_asin.c src/double/ieee754-core/e_atan2.c src/double/ieee754-core/e_cosh.c src/double/ieee754-core/e_exp.c src/double/ieee754-core/e_fmod.c src/double/ieee754-core/e_log.c src/double/ieee754-core/e_log10.c src/double/ieee754-core/e_pow.c src/double/ieee754-core/e_rem_pio2.c src/double/ieee754-core/e_scalb.c src/double/ieee754-core/e_sinh.c src/double/ieee754-core/e_sqrt.c src/double/ieee754-core/e_hypot.c src/double/ieee754-api/w_acos.c src/double/ieee754-api/w_asin.c src/double/ieee754-api/w_atan2.c src/double/ieee754-api/w_cosh.c src/double/ieee754-api/w_exp.c src/double/ieee754-api/w_fmod.c src/double/ieee754-api/w_log.c src/double/ieee754-api/w_log10.c src/double/ieee754-api/w_pow.c src/double/ieee754-api/w_scalb.c src/double/ieee754-api/w_sinh.c src/double/ieee754-api/w_sqrt.c src/double/ieee754-api/w_hypot.c src/double/ieee754-core/e_gamma.c src/double/ieee754-api/w_gamma.c src/double/ieee754-core/e_gamma_r.c src/double/ieee754-api/w_gamma_r.c src/double/ieee754-core/e_lgamma.c src/double/ieee754-api/w_lgamma.c src/double/ieee754-core/e_lgamma_r.c src/double/ieee754-api/w_lgamma_r.c src/double/internal/k_cos.c src/double/internal/k_rem_pio2.c src/double/internal/k_sin.c src/double/internal/k_tan.c src/float/internal/kf_cos.c src/float/internal/kf_sin.c src/float/internal/kf_rem_pio2.c src/float/internal/kf_tan.c src/double/portable-api/s_atan.c src/double/portable-api/s_ceil.c src/double/portable-api/s_copysign.c src/double/portable-api/s_cos.c src/double/portable-api/s_expm1.c src/double/portable-api/s_fabs.c src/double/portable-api/s_finite.c src/double/portable-api/s_floor.c src/double/portable-api/s_frexp.c src/double/portable-api/s_isnan.c src/double/portable-api/s_ldexp.c src/double/portable-api/s_rint.c src/double/portable-api/s_scalbn.c src/double/portable-api/s_sin.c src/double/portable-api/s_tan.c src/double/portable-api/s_modf.c src/double/portable-api/s_tanh.c src/float/ieee754-core/ef_rem_pio2.c src/float/ieee754-core/ef_sqrt.c src/float/ieee754-api/wf_sqrt.c src/float/ieee754-core/ef_pow.c src/float/ieee754-api/wf_pow.c src/float/ieee754-core/ef_exp.c src/float/ieee754-api/wf_exp.c src/float/ieee754-core/ef_asin.c src/float/ieee754-api/wf_asin.c src/float/ieee754-core/ef_log.c src/float/ieee754-api/wf_log.c src/float/ieee754-core/ef_log10.c src/float/ieee754-api/wf_log10.c src/float/ieee754-core/ef_hypot.c src/float/ieee754-api/wf_hypot.c src/float/ieee754-core/ef_fmod.c src/float/ieee754-api/wf_fmod.c src/float/ieee754-core/ef_remainder.c src/float/ieee754-api/wf_remainder.c src/float/ieee754-core/ef_scalb.c src/float/ieee754-api/wf_scalb.c src/float/ieee754-core/ef_acos.c src/float/ieee754-api/wf_acos.c src/float/ieee754-core/ef_atan2.c src/float/ieee754-api/wf_atan2.c src/float/ieee754-core/ef_acosh.c src/float/ieee754-api/wf_acosh.c src/float/ieee754-core/ef_atanh.c src/float/ieee754-api/wf_atanh.c src/float/ieee754-core/ef_cosh.c src/float/ieee754-api/wf_cosh.c src/float/ieee754-core/ef_j0.c src/float/ieee754-api/wf_j0.c src/float/ieee754-core/ef_j1.c src/float/ieee754-api/wf_j1.c src/float/ieee754-core/ef_jn.c src/float/ieee754-api/wf_jn.c src/float/ieee754-core/ef_sinh.c src/float/ieee754-api/wf_sinh.c src/float/portable-api/sf_asinh.c src/float/portable-api/sf_ilogb.c src/float/portable-api/sf_copysign.c src/float/portable-api/sf_sin.c src/float/portable-api/sf_finite.c src/float/portable-api/sf_erf.c src/float/portable-api/sf_isnan.c src/float/portable-api/sf_floor.c src/float/portable-api/sf_modf.c src/float/portable-api/sf_atan.c src/float/portable-api/sf_ldexp.c src/float/portable-api/sf_nextafter.c src/float/portable-api/sf_tan.c src/float/portable-api/sf_cbrt.c src/float/portable-api/sf_expm1.c src/float/portable-api/sf_frexp.c src/float/portable-api/sf_log1p.c src/float/portable-api/sf_rint.c src/float/portable-api/sf_tanh.c src/float/portable-api/sf_ceil.c src/float/portable-api/sf_fabs.c src/float/portable-api/sf_logb.c src/float/portable-api/sf_scalbn.c src/float/portable-api/sf_cos.c src/float/portable-api/sf_significand.c src/complex/cabs.c src/complex/cabsf.c src/complex/carg.c src/complex/cargf.c src/complex/creal.c src/complex/crealf.c src/complex/cimag.c src/complex/cimagf.c src/complex/conj.c src/complex/conjf.c src/complex/cacos.c src/complex/cacosf.c src/complex/cacosh.c src/complex/cacoshf.c src/complex/casin.c src/complex/casinf.c src/complex/casinh.c src/complex/casinhf.c src/complex/catan.c src/complex/catanf.c src/complex/catanh.c src/complex/catanhf.c src/complex/ccos.c src/complex/ccosf.c src/complex/ccosh.c src/complex/ccoshf.c src/complex/cephes_subr.c src/complex/cephes_subrf.c src/complex/cexp.c src/complex/cexpf.c src/complex/clog.c src/complex/clogf.c src/complex/cpow.c src/complex/cpowf.c src/complex/cproj.c src/complex/cprojf.c src/complex/csin.c src/complex/csinf.c src/complex/csinh.c src/complex/csinhf.c src/complex/csqrt.c src/complex/csqrtf.c src/complex/ctan.c src/complex/ctanf.c src/complex/ctanh.c src/complex/ctanhf.c
OBJECTS := $(COMPILE:.cxx=.o.d)
OBJECTS := $(OBJECTS:.cpp=.o.d)
OBJECTS := $(OBJECTS:.c=.o.d)
OBJECTS := $(OBJECTS:.S=.o.d)

$(LIBRARY).stamp: $(OBJECTS)
	$(AR) rcs $(PREFIX)/lib/$(@:.stamp=) $(foreach obj,$?,$(if $(obj:%.o=),$(dir $(obj))$(OBJECT_PREFIX)_$(notdir $(obj:.o.d=.o)),$(obj)))
	@cat $(foreach obj,$^,$(obj:.o=.o.d)) > $(@:.stamp=.deps)
	@touch $@

headers: mlt_headers $(PREFIX)/include/math.h $(PREFIX)/include/complex.h $(PREFIX)/include/sys/ieeefp.h

$(PREFIX)/include/math.h: $(REPOSITORY)/$(PACKAGE)/include/math.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/complex.h: $(REPOSITORY)/$(PACKAGE)/include/complex.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/sys/ieeefp.h: $(REPOSITORY)/$(PACKAGE)/include/sys/ieeefp.h
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

include $(REPOSITORY)/pkgconf/rules.mak

