CFLAGS+=-std=c99 -pedantic-errors -Wall -Werror -Wno-unused -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700
#CFLAGS+=-DX_PS -DX_TPS -DX_TYM -DX_RPP_TPP

all:
	for i in *.c; do \
		LC_ALL=C $(CC) $(CFLAGS) -c $$i 2>&1; \
	done |grep -v 'Each undeclared identifier is reported only once' |grep -v 'for each function it appears in'
	$(CC) $(LDFLAGS) -lcrypt -ldl -lm -lpthread -lrt *.o -o main 2>&1

clean:
	rm -f main *.o

