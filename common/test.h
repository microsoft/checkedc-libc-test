#include <stdio.h>
#include <stdarg.h>

extern struct test {
	int failed;
	const char *name;
} test__;

#define error(...) error__(__FILE__, __LINE__, __VA_ARGS__)

static void error__(const char *n, int l, const char *s, ...) {
	va_list ap;

	test__.failed = 1;
	fprintf(stderr, "- ERROR %s at %s:%d: ", test__.name, n, l);
	va_start(ap, s);
	vfprintf(stderr, s, ap);
	va_end(ap);
}
