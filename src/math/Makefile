CFLAGS+=-g -pipe -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wno-unused-function -Wno-missing-braces
CFLAGS+=-Wno-unknown-pragmas -fno-builtin -frounding-math
CFLAGS+=-D_GNU_SOURCE -O0
LDFLAGS+=-g -lm
BUILD?=.

SRC=$(sort $(wildcard *.c))
OBJ=$(SRC:%.c=$(BUILD)/%.o)
BINOBJ=$(filter-out $(BUILD)/util.o,$(OBJ))
BIN=$(BINOBJ:.o=)

-include ../../config.mak

all: $(BIN)
run: all
	@N=0; for i in $(BIN);do ./$$i || N=$$((N+1)); done; [ "$$N" = 0 ] && echo PASS || echo FAILS: $$N
clean:
	rm -f $(OBJ) $(BIN)

$(BUILD):
	mkdir -p $@
$(BIN): $(BUILD)/util.o
$(OBJ): util.h | $(BUILD)
$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
%: %.c

%: %.o
	$(CC) $(LDFLAGS) -o $@ $^

.PRECIOUS: $(OBJ)
