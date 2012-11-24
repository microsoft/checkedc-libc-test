CFLAGS+=-g -pipe -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wno-unused-function -Wno-missing-braces
CFLAGS+=-Wno-unknown-pragmas -fno-builtin -frounding-math -D_GNU_SOURCE
LDFLAGS+=-g -lm

SRC=$(sort $(wildcard *.c))
OBJ=$(SRC:.c=.o)
BINOBJ=$(filter-out util.o,$(OBJ))
BIN=$(BINOBJ:.o=)

#include ../../config.mak

all: $(BIN)
run: all
	@N=0; for i in $(BIN);do ./$$i || N=$$((N+1)); done; [ "$$N" = 0 ] && echo PASS || echo FAILS: $$N
clean:
	rm -f $(OBJ) $(BIN)

$(BIN): util.o
$(OBJ): util.h
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
%: %.c
%: %.o
	$(CC) $(LDFLAGS) -o $@ $^

.PRECIOUS: $(OBJ)
