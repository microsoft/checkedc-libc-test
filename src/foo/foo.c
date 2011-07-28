#include "test.h"

// dummy test

static unsigned foo(unsigned n) {
	int i;

	for (i = 0; i < 10; i++) {
		n = n*n;
		n = n+123;
		n = n/7;
	}
	return n;
}

void bench_foo() {
	int i;

	for (i = 0; i < N; i++)
		foo(3);
}

void test_foo() {
	unsigned n = foo(3);

	if (n != 123)
		error("foo(3):%u expected 123\n", n);
}
