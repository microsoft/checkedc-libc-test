#include "test.h"

// dummy test

static int foo(int n) {
	int i;

	for (i = 0; n > 1 && i < 100; i++) {
		if (n % 2)
			n = 3*n + 1;
		else
			n /= 2;
	}
	return n;
}

void test_foo() {
	int n = foo(123);

	if (n != 1)
		error("foo(123):%d expected 1\n", n);
}

void bench_foo(int N) {
	int i;

	for (i = 0; i < N; i++)
		foo(123);
}

unsigned short ds = 12345;
unsigned short rs = 0;
void bench_div_short(int N) {
	int i;

	for (i = 0; i < N; i++)
		rs += (unsigned short)i/ds;
}

unsigned int di = 12345;
unsigned int ri = 0;
void bench_div_int(int N) {
	unsigned int i;

	for (i = 0; i < N; i++)
		ri += i/di;
}
