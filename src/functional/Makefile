CFLAGS+=-pipe -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wno-unused-function -Wno-missing-braces
LDFLAGS+=
LDLIBS+=
BUILD?=.

SRC=$(sort $(wildcard *.c))
OBJ=$(SRC:%.c=$(BUILD)/%.o)
DSOOBJ=$(filter %_dso.o,$(OBJ))
BINOBJ=$(filter-out %_dso.o,$(OBJ))
NO_DL_OBJ=$(filter-out %dlopen.o,$(BINOBJ))
DSO=$(DSOOBJ:.o=.so)
BIN=$(BINOBJ:.o=)
BIN_STATIC=$(NO_DL_OBJ:.o=-static)
ALL=$(BIN) $(BIN_STATIC) $(DSO)

-include ../../config.mak

all: $(ALL)
run: all
	@N=0; A=0; for i in $(BIN) $(BIN_STATIC);do \
		A=$$((A+1)); ./$$i || { N=$$((N+1)); echo FAIL $$i; } \
	done; \
	[ "$$N" = 0 ] && echo PASS || echo FAILS: $$N/$$A
clean:
	rm -f $(OBJ) $(ALL)

$(BUILD):
	mkdir -p $@
$(OBJ): test.h | $(BUILD)
$(DSOOBJ): CFLAGS+=-fPIC
$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< || echo BUILDERROR $@
%.so: %.o
	$(CC) -shared $(LDFLAGS) -o $@ $< $(LDLIBS) || echo BUILDERROR $@
%-static: %.o
	$(CC) -static $(LDFLAGS) -o $@ $< $(LDLIBS) || echo BUILDERROR $@
%: %.o
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS) || echo BUILDERROR $@

$(BUILD)/dlopen: LDLIBS+=-ldl -rdynamic
$(BUILD)/pthread%: LDLIBS+=-lpthread
$(BUILD)/sem $(BUILD)/sem-static: LDLIBS+=-lpthread -lrt
$(BUILD)/strtod_simple $(BUILD)/strtod_simple-static: LDLIBS+=-lm
$(BUILD)/tgmath tgmath-static: LDLIBS+=-lm
# adding ./lib.so through LDLIBS instead of $^ in the implicit rule because make removes the leading ./ from dependencies
$(BUILD)/tls_align: LDLIBS+=$(BUILD)/tls_align_dso.so
$(BUILD)/tls_align: $(BUILD)/tls_align_dso.so
# make bug: tls_align target specific flags are also set for tls_align_dso.so when both target is built
$(BUILD)/tls_align_dso.so: LDLIBS=
$(BUILD)/tls_align-static: LDLIBS+=$(BUILD)/tls_align_dso.o
$(BUILD)/tls_align-static: $(BUILD)/tls_align_dso.o
$(BUILD)/tls_align_dlopen: LDLIBS+=-ldl
$(BUILD)/tls_init tls_init-static: LDLIBS+=-lpthread

