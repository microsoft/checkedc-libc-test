#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

/* TODO: not thread-safe nor fork-safe */
static volatile int test_status;

#define TEST_LOC2(l) __FILE__ ":" #l
#define TEST_LOC1(l) TEST_LOC2(l)
#define error(...) test_printf("ERROR " TEST_LOC1(__LINE__) ": " __VA_ARGS__)

static int test_printf(const char *s, ...)
{
	va_list ap;
	char buf[512];
	int n;

	test_status = 1;
	va_start(ap, s);
	n = vsnprintf(buf, sizeof buf, s, ap);
	va_end(ap);
	if (n < 0)
		n = 0;
	else if (n >= sizeof buf) {
		n = sizeof buf;
		buf[n - 1] = '\n';
		buf[n - 2] = '.';
		buf[n - 3] = '.';
		buf[n - 4] = '.';
	}
	return write(1, buf, n);
}

