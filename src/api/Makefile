CFLAGS+=-std=c99 -Wall -Werror -Wno-unused -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700

all:
	for i in *.c; do \
		$(CC) $(CFLAGS) -c $$i 2>&1; \
	done
	$(CC) $(LDFLAGS) -lcrypt -ldl -lm -lpthread -lrt *.o -o main

clean:
	rm -f main *.o

