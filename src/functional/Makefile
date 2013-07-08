CFLAGS+=-pipe -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wno-unused-function -Wno-missing-braces
LDFLAGS+=
LDLIBS+=

SRC=$(sort $(wildcard *.c))
OBJ=$(SRC:.c=.o)
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

$(OBJ): test.h
$(DSOOBJ): CFLAGS+=-fPIC
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< || echo BUILDERROR $@
%.so: %.o
	$(CC) -shared $(LDFLAGS) -o $@ $< $(LDLIBS) || echo BUILDERROR $@
%-static: %.o
	$(CC) -static $(LDFLAGS) -o $@ $< $(LDLIBS) || echo BUILDERROR $@
%: %.o
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS) || echo BUILDERROR $@

dlopen: LDLIBS+=-ldl -rdynamic
pthread%: LDLIBS+=-lpthread
sem sem-static: LDLIBS+=-lpthread -lrt
strtod_simple strtod_simple-static: LDLIBS+=-lm
tgmath tgmath-static: LDLIBS+=-lm
# adding ./lib.so through LDLIBS instead of $^ in the implicit rule because make removes the leading ./ from dependencies
tls_align: LDLIBS+=./tls_align_dso.so
tls_align: tls_align_dso.so
# make bug: tls_align target specific flags are also set for tls_align_dso.so when both target is built
tls_align_dso.so: LDLIBS=
tls_align-static: LDLIBS+=tls_align_dso.o
tls_align-static: tls_align_dso.o
tls_align_dlopen: LDLIBS+=-ldl
tls_init tls_init-static: LDLIBS+=-lpthread

