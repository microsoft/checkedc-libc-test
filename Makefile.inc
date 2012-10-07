CFLAGS+=-g -pipe -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wno-unused-function -Wno-missing-braces
LDFLAGS+=-g

SRC=$(sort $(wildcard *.c))
OBJ=$(SRC:.c=.o)
DSOOBJ=$(filter %_dso.o,$(OBJ))
BINOBJ=$(filter-out %_dso.o,$(OBJ))
DSO=$(DSOOBJ:.o=.so)
BIN=$(BINOBJ:.o=)

ROOT=../..
include $(ROOT)/config.mak

all: $(BIN) $(DSO)
run: all
	@N=0; for i in $(BIN);do ./$$i || N=$$((N+1)); done; [ "$$N" = 0 ] && echo PASS || echo FAILS: $$N
clean:
	rm -f $(OBJ) $(DSO) $(BIN)

$(OBJ): test.h
$(DSOOBJ): CFLAGS += -fPIC
%.so: %.o
	$(CC) $(LDFLAGS) -shared -o $@ $<
%: %.o
	$(CC) $(LDFLAGS) -o $@ $(patsubst %.so,./%.so,$+)
