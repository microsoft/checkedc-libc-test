SRCS:=$(sort $(wildcard src/*/*.c))
OBJS:=$(SRCS:%.c=%.o)
DIRS:=$(sort $(wildcard src/*))
NAMES:=$(OBJS:.o=)
CFLAGS:=-Isrc/common
LDLIBS:=src/common/libtest.a

all:
%.mk:

config.mak:
	cp config.mak.def $@
-include config.mak

define default_template
$(1).BINS_TEMPL:=bin bin-static
$(1).NAMES:=$$(filter $(1)/%,$$(NAMES))
$(1).OBJS:=$$($(1).NAMES:%=%.o)
endef
$(foreach d,$(DIRS),$(eval $(call default_template,$(d))))
src/common.BINS_TEMPL:=
src/api.BINS_TEMPL:=
src/math.BINS_TEMPL:=bin

define template
D:=$$(patsubst %/,%,$$(dir $(1)))
N:=$(1)
$(1).BINS := $$($$(D).BINS_TEMPL:bin%=$(1)%)
-include $(1).mk
#$$(warning D $$(D) T $$($$(D).BINS_TEMPL) B $$($(1).BINS))
$(1) $(1)-static: $$($(1).OBJS)
$(1).so: $$($(1).LOBJS)
# make sure dynamic and static binaries are not run parallel (matters for some tests eg ipc)
$(1)-static.err: $(1).err
endef
$(foreach n,$(NAMES),$(eval $(call template,$(n))))

BINS:=$(foreach n,$(NAMES),$($(n).BINS)) src/api/main
LIBS:=$(foreach n,$(NAMES),$($(n).LIBS)) src/common/run
ERRS:=$(BINS:%=%.err)

debug:
	@echo NAMES $(NAMES)
	@echo BINS $(BINS)
	@echo LIBS $(LIBS)
	@echo ERRS $(ERRS)
	@echo DIRS $(DIRS)

define target_template
$(1).ERRS:=$$(filter $(1)/%,$$(ERRS))
$(1)/all: $(1)/REPORT
# TODO: src/common/run collides with the run binary target
$(1)/run: $(1)/cleanerr $(1)/REPORT
$(1)/cleanerr:
	rm -f $$(filter-out $(1)/%-static.err,$$($(1).ERRS))
$(1)/clean:
	rm -f $$(filter $(1)/%,$$(OBJS) $$(BINS) $$(LIBS)) $(1)/*.err
$(1)/REPORT: $$($(1).ERRS)
	cat $(1)/*.err >$$@
run: $(1)/run
REPORT: $(1)/REPORT
.PHONY: $(1)/all $(1)/clean
endef
$(foreach d,$(DIRS),$(eval $(call target_template,$(d))))

src/common/libtest.a: $(src/common.OBJS)
	rm -f $@
	$(AR) rc $@ $^
	$(RANLIB) $@

$(ERRS): src/common/run
$(BINS) $(LIBS): src/common/libtest.a
$(OBJS): src/common/test.h

src/common/mtest.o: src/common/mtest.h
$(src/math.OBJS): src/common/mtest.h

src/api/main: $(src/api.OBJS)
src/api/main.OBJS:=$(src/api.OBJS)
$(src/api.OBJS):CFLAGS+=-pedantic-errors -Werror -Wno-unused -D_XOPEN_SOURCE=700
$(src/api.OBJS):CFLAGS+=-DX_PS -DX_TPS -DX_SS

all:REPORT
run:REPORT
clean:
	rm -f $(OBJS) $(BINS) $(LIBS) src/common/libtest.a src/common/run src/*/*.err
cleanall: clean
	rm -f REPORT src/*/REPORT
REPORT:
	cat $^ |tee $@

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
	src/common/run ./$< 2>/dev/null >$@ || true

.PHONY: all run clean cleanall

