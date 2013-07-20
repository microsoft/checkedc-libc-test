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
		t_error("clrearenv: %s\n", strerror(errno));
	if (putenv("TEST=1"))
		t_error("putenv: %s\n", strerror(errno));
	if ((s=environ[1]))
		t_error("environ[1]: %p, wanted 0\n", s);
	if (!(s=getenv("TEST")))
		t_error("getenv(\"TEST\"): 0, wanted \"1\"\n");
	if (strcmp(s,"1") != 0)
		t_error("getenv(\"TEST\"): \"%s\", wanted \"1\"\n", s);
	if (unsetenv("TEST"))
		t_error("unsetenv: %s\n", strerror(errno));
	if ((s=*environ))
		t_error("*environ: %p != 0\n", s);
	if ((s=getenv("TEST")))
		t_error("getenv(\"TEST\"): %p, wanted 0\n", s);
	if (setenv("TEST", "2", 0))
		t_error("setenv: %s\n", strerror(errno));
	if (strcmp(s=getenv("TEST"),"2") != 0)
		t_error("getenv(\"TEST\"): \"%s\", wanted \"2\"\n", s);
	if (setenv("TEST", "3", 0))
		t_error("setenv: %s\n", strerror(errno));
	if (strcmp(s=getenv("TEST"),"2") != 0)
		t_error("getenv(\"TEST\"): \"%s\", wanted \"2\"\n", s);
	if (setenv("TEST", "3", 1))
		t_error("setenv: %s\n", strerror(errno));
	if (strcmp(s=getenv("TEST"),"3") != 0)
		t_error("getenv(\"TEST\"): \"%s\", wanted \"3\"\n", s);
	/* test failures */
	if ((r=setenv("","",0)) != -1 || errno != EINVAL)
		t_error("setenv(\"\",\"\",0): %d, errno: %d (%s), wanted -1, %d (EINVAL)\n", r, errno, strerror(errno), EINVAL);
	if ((r=setenv(0,"",0)) != -1 || errno != EINVAL)
		t_error("setenv(0,\"\",0): %d, errno: %d (%s), wanted -1, %d (EINVAL)\n", r, errno, strerror(errno), EINVAL);
	return t_status;
}
