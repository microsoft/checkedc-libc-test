#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "test.h"

extern char **environ;

int main()
{
	char *s;
	int r;

	if (clearenv() || (environ && *environ))
		error("clrearenv: %s\n", strerror(errno));
	if (putenv("TEST=1"))
		error("putenv: %s\n", strerror(errno));
	if ((s=environ[1]))
		error("environ[1]: %p, wanted 0\n", s);
	if (!(s=getenv("TEST")))
		error("getenv(\"TEST\"): 0, wanted \"1\"\n");
	if (strcmp(s,"1") != 0)
		error("getenv(\"TEST\"): \"%s\", wanted \"1\"\n", s);
	if (unsetenv("TEST"))
		error("unsetenv: %s\n", strerror(errno));
	if ((s=*environ))
		error("*environ: %p != 0\n", s);
	if ((s=getenv("TEST")))
		error("getenv(\"TEST\"): %p, wanted 0\n", s);
	if (setenv("TEST", "2", 0))
		error("setenv: %s\n", strerror(errno));
	if (strcmp(s=getenv("TEST"),"2") != 0)
		error("getenv(\"TEST\"): \"%s\", wanted \"2\"\n", s);
	if (setenv("TEST", "3", 0))
		error("setenv: %s\n", strerror(errno));
	if (strcmp(s=getenv("TEST"),"2") != 0)
		error("getenv(\"TEST\"): \"%s\", wanted \"2\"\n", s);
	if (setenv("TEST", "3", 1))
		error("setenv: %s\n", strerror(errno));
	if (strcmp(s=getenv("TEST"),"3") != 0)
		error("getenv(\"TEST\"): \"%s\", wanted \"3\"\n", s);
	/* test failures */
	if ((r=setenv("","",0)) != -1 || errno != EINVAL)
		error("setenv(\"\",\"\",0): %d, errno: %d (%s), wanted -1, %d (EINVAL)\n", r, errno, strerror(errno), EINVAL);
	if ((r=setenv(0,"",0)) != -1 || errno != EINVAL)
		error("setenv(0,\"\",0): %d, errno: %d (%s), wanted -1, %d (EINVAL)\n", r, errno, strerror(errno), EINVAL);
	return test_status;
}
