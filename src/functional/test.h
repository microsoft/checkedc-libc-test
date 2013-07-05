#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

/* TODO: not thread-safe nor fork-safe */
static volatile int test_status;

#define error(...) test_error(__FILE__, __LINE__, __VA_ARGS__)

static int test_error(const char *fn, int l, const char *s, ...)
{
	va_list ap;
	char buf[512];
	int n, k;

	test_status = 1;
	n = snprintf(buf, sizeof buf, "ERROR %s:%d: ", fn, l);
	if (n < 0)
		n = 0;
	else if (n >= sizeof buf)
		n = sizeof buf;
	va_start(ap, s);
	k = vsnprintf(buf + n, sizeof buf - n, s, ap);
	va_end(ap);
	if (k < 0)
		k = 0;
	else if (k >= sizeof buf - n) {
		k = sizeof buf - n;
		buf[n + k - 1] = '\n';
		buf[n + k - 2] = '.';
		buf[n + k - 3] = '.';
		buf[n + k - 4] = '.';
	}
	return write(1, buf, n + k);
}

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

