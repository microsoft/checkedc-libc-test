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

void bench_foo() {
	int i;

	for (i = 0; i < N; i++)
		foo(123);
}

void test_foo() {
	int n = foo(123);

	if (n != 1)
		error("foo(123):%d expected 1\n", n);
}
