#include <stdio.h>
#include <stdarg.h>
#define error(...) test_error(__FILE__, __LINE__, __VA_ARGS__)

static int test_status;

static int test_error(const char *n, int l, const char *s, ...)
{
	va_list ap;

	if (test_status == 0)
		printf("FAIL\n");
	test_status = 1;
	printf(" ERROR %s:%d: ", n, l);
	va_start(ap, s);
	vprintf(s, ap);
	va_end(ap);
	return -1;
}

