CFLAGS+=-std=c99 -pedantic-errors -Wall -Werror -Wno-unused -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700
#CFLAGS+=-DX_PS -DX_TPS -DX_TYM -DX_RPP_TPP -DX_FMTMSG -DX_NDBM
LDFLAGS+=-lcrypt -ldl -lm -lpthread -lrt

SRC=$(sort $(wildcard *.c))
ERR=$(SRC:.c=.err)

-include ../../config.mak

all: all.err

run: all.err
	cat $<

all.err: $(ERR)
	LC_ALL=C $(CC) $(LDFLAGS) -o main *.o 2>main.err || true
	cat $(ERR) |\
		grep -v 'In function .f.' |\
		grep -v 'Each undeclared identifier is reported only once' |\
		grep -v 'for each function it appears in' >$@ || true

%.err: %.c
	LC_ALL=C $(CC) $(CFLAGS) -c $< 2>$@ || true

clean:
	rm -f main *.o *.err
