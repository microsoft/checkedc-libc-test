#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

void bench_stdio_putcgetc(int N) {
	FILE *f = tmpfile();
	size_t i;
	size_t cs = 0;

	for (i=0; i<N; i++)
		putc('x', f);
	fseeko(f, 0, SEEK_SET);
	for (i=0; i<N; i++)
		cs += getc(f);
	fclose(f);
	if (cs != (size_t)N*'x')
		abort();
}

void bench_stdio_putcgetc_unlocked(int N) {
	FILE *f = tmpfile();
	size_t i;
	size_t cs = 0;

	for (i=0; i<N; i++)
		putc_unlocked('x', f);
	fseeko(f, 0, SEEK_SET);
	for (i=0; i<N; i++)
		cs += getc_unlocked(f);
	fclose(f);
	if (cs != (size_t)N*'x')
		abort();
}
