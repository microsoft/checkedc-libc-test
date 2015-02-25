#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "test.h"

#define N 400
static char buf[N];
static char buf2[N];

static void *(*volatile pmemset)(void *, int, size_t);

static void *aligned(void *p)
{
	return (void*)(((uintptr_t)p + 63) & -64U);
}

static void test_align(int align, int len)
{
	char *s = aligned(buf+64);
	char *want = aligned(buf2+64);
	char *p;
	int i;

	if (s - buf + align + len > N)
		abort();
	for (i = 0; i < N; i++)
		buf[i] = buf2[i] = ' ';
	for (i = 0; i < len; i++)
		want[align+i] = '#';
	p = pmemset(s+align, '#', len);
	if (p != s+align)
		t_error("memset(%p,...) returned %p\n", s+align, p);
	for (i = 0; i < N; i++)
		if (buf[i] != buf2[i]) {
			t_error("memset(align %d, '#', %d) failed\n", align, len);
			t_printf("got : %.*s\n", align+len+1, s);
			t_printf("want: %.*s\n", align+len+1, want);
			break;
		}
}

static void test_value(int c)
{
	int i;

	pmemset(buf, c, 10);
	for (i = 0; i < 10; i++)
		if ((unsigned char)buf[i] != (unsigned char)c) {
			t_error("memset(%d) failed: got %d\n", c, buf[i]);
			break;
		}
}

int main(void)
{
	int i,j,k;

	pmemset = memset;

	for (i = 0; i < 16; i++)
		for (j = 0; j < 200; j++)
			test_align(i,j);

	test_value('c');
	test_value(0);
	test_value(-1);
	test_value(-5);
	test_value(0xab);
	return t_status;
}
