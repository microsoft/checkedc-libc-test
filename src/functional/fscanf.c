#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include "test.h"

#define T(f, x, m) do { \
	r = (f); \
	if (r != (x)) \
		error("%s failed (got %d, expected %d, errno \"%s\") (%s)\n", \
			#f, r, x, errno ? strerror(errno) : "", m); \
	errno = 0; \
} while (0)

#define S(s, x, m) do { \
	if (strcmp(s, x) != 0) \
		error("got [%s] want [%s] (%s)\n", s, x, m); \
} while(0)

int main(void)
{
	int r, x, y;
	char a[100], b[100];
	int p[2];
	FILE *f;

	T(pipe(p), 0, "open pipe");
	T(!(f = fdopen(p[0], "rb")), 0, "fdopen pipe");
	if (!f) {
		close(p[0]);
		close(p[1]);
		return test_status;
	}

	T(write(p[1], "hello, world\n", 13), 13, "write to pipe");
	T(fscanf(f, "%s %[own]", a, b), 2, "");
	S(a, "hello,", "wrong result for %s");
	S(b, "wo", "wrong result for %[own]");
	T(fgetc(f), 'r', "fgetc 'r'");

	T(write(p[1], " 0x12 0x34", 10), 10, "");
	T(fscanf(f, "ld %5i%2i", &x, &y), 1, "");
	T(x, 0x12, "");
	T(fgetc(f), '3', "fgetc '3'");

	fclose(f);
	close(p[1]);
	return test_status;
}
