#define _XOPEN_SOURCE 700
#include "test.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

extern char **environ;
int clearenv(void);

void test_env() {
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
	if ((r=setenv("","",0)) != -1 || errno != EINVAL)
		error("setenv(\"\",\"\"): %d, errno: %d (%s), wanted -1, %d (EINVAL)\n", r, errno, strerror(errno), EINVAL);
}
