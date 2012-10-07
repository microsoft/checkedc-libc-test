CFLAGS=-I. -Wall -fno-builtin -ffloat-store -D_GNU_SOURCE
U=mpfr
T=$(wildcard t*.c)

all: gen check

gen: gen.c util.c mp.c $(U)/lib/libmpfr.a $(U)/lib/libgmp.a
	musl-gcc -o $@ $(CFLAGS) -I$(U)/include $^

check: gen.c util.c mplibm.c
	musl-gcc -o $@ $(CFLAGS) -lm $^

#genlibm: gen.c util.c mplibm.c
#	musl-gcc -o $@ $(CFLAGS) -lm $^

clean:
	rm -f gen check genlibm

