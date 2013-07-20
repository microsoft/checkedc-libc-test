SRCS:=$(sort $(wildcard src/*/*.c))
OBJS:=$(SRCS:%.c=%.o)
DIRS:=$(sort $(wildcard src/*))
NAMES:=$(OBJS:.o=)
SPEC_PATTERNS:=src/common/% src/api/% src/math/%
CFLAGS:=-Isrc/common
LDLIBS:=src/common/libtest.a

-include config.mak

all:
%.mk:

define template
$(1).BINS := $(1) $(1)-static
D:=$$(dir $(1))
N:=$(1)
-include $(1).mk
$(1) $(1)-static: $$($(1).OBJS)
$(1).so: $$($(1).LOBJS)
# make sure dynamic and static binaries are not run parallel (matters for some tests eg ipc)
$(1)-static.err: $(1).err
endef

$(foreach n,$(filter-out $(SPEC_PATTERNS),$(NAMES)),$(eval $(call template,$(n))))

MBINS:=$(filter src/math/%,$(NAMES))
BINS:=$(foreach n,$(NAMES),$($(n).BINS)) src/api/main $(MBINS)
LIBS:=$(foreach n,$(NAMES),$($(n).LIBS))
ERRS:=$(BINS:%=%.err)

define target_template
$(1)/all: $(1)/REPORT
$(1)/clean:
	rm -f $$(filter $(1)/%,$$(OBJS) $$(BINS) $$(LIBS)) $(1)/*.err
$(1)/REPORT: $$(filter $(1)/%,$$(ERRS))
	cat $(1)/*.err >$$@
REPORT: $(1)/REPORT
.PHONY: $(1)/all $(1)/clean
endef

$(foreach d,$(DIRS),$(eval $(call target_template,$(d))))

src/common/all: src/common/libtest.a

all:REPORT
clean:
	rm -f $(OBJS) $(BINS) $(LIBS) src/common/libtest.a src/*/*.err
cleanall: clean
	rm -f REPORT src/*/REPORT
REPORT:
	cat $^ |tee $@

src/common/libtest.a: $(filter src/common/%,$(OBJS))
	rm -f $@
	$(AR) rc $@ $^
	$(RANLIB) $@

$(BINS) $(LIBS): src/common/libtest.a
$(OBJS): src/common/test.h

src/common/mtest.o: src/common/mtest.h
$(MBINS:%=%.o): src/common/mtest.h

IOBJS:=$(filter src/api/%,$(OBJS))
src/api/main: $(IOBJS)
src/api/main.OBJS:=$(IOBJS)
$(IOBJS):CFLAGS+=-pedantic-errors -Werror -Wno-unused -D_XOPEN_SOURCE=700
$(IOBJS):CFLAGS+=-DX_PS -DX_TPS -DX_SS

%.o: %.c
	$(CC) $(CFLAGS) $($*.CFLAGS) -c -o $@ $< 2>$@.err || echo BUILDERROR $@
%.s: %.c
	$(CC) $(CFLAGS) $($*.CFLAGS) -S -o $@ $< || echo BUILDERROR $@
%.lo: %.c
	$(CC) $(CFLAGS) $($*.CFLAGS) -fPIC -DSHARED -c -o $@ $< 2>$@.err || echo BUILDERROR $@
%.so: %.lo
	$(CC) -shared $(LDFLAGS) $($@.LDFLAGS) -o $@ $< $($*.LOBJS) $(LDLIBS) $($@.LDLIBS) 2>$@.err || echo BUILDERROR $@
%-static: %.o
	$(CC) -static $(LDFLAGS) $($@.LDFLAGS) -o $@ $< $($*.OBJS) $(LDLIBS) $($@.LDLIBS) 2>$@.err || echo BUILDERROR $@
%: %.o
	$(CC) $(LDFLAGS) $($@.LDFLAGS) -o $@ $< $($@.OBJS) $(LDLIBS) $($@.LDLIBS) 2>$@.err || echo BUILDERROR $@

%.o.err: %.o
	touch $@
%.lo.err: %.lo
	touch $@
%.so.err: %.so
	touch $@
%.err: %
# TODO: proper wrapping that records exit status
	./$< 2>/dev/null >$@ || true

.PHONY: all clean cleanall

