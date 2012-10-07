#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <sys/resource.h>
#include "test.h"

static void setrl(int r, long lim)
{
	struct rlimit rl;

	if (getrlimit(r, &rl))
		error("getrlimit %d: %s\n", r, strerror(errno));
	rl.rlim_cur = lim;
	if (setrlimit(r, &rl))
		error("setrlimit %d: %s\n", r, strerror(errno));
}

int main(void)
{
	enum {n = 8*1024*1024};
	char *s = malloc(n);
	int i;
	float f;
	char c;

	if (!s)
		return error("out of memory");
	setrl(RLIMIT_STACK, 128*1024);

	for (i = 0; i < n; i++) s[i] = '1';
	s[n-3] = ' ';
	s[n-1] = 0;

	/*
	 * stack overflow if scanf copies s on the stack (glibc)
	 * same issue with %d except then storing the conversion
	 * result is undefined behaviour
	 */
	i = sscanf(s, "%f %c", &f, &c);

	if (i != 2)
		error("sscanf returned %d, want 2\n", i);
	if (f != INFINITY)
		error("sscanf(longnum, \"%%f\") read %f, want inf\n", f);
	if (c != '1')
		error("sscanf(\"1\", %%c) read '%c', want '1'\n", c);
	free(s);
	return test_status;
}
