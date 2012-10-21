#include <dlfcn.h>
#include "test.h"

int foo;

int main()
{
	void *h, *g;
	int *i, *i2;
	char *s;
	void (*f)(void);

	h = dlopen("./dlopen_dso.so", RTLD_LAZY|RTLD_LOCAL);
	if (!h)
		error("dlopen ./dlopen_dso.so failed: %s\n", dlerror());
	i = dlsym(h, "i");
	if (!i)
		error("dlsym i failed: %s\n", dlerror());
	if (*i != 1)
		error("initialization failed: want i=1 got i=%d\n", *i);
	f = (void (*)(void))dlsym(h, "f");
	if (!f)
		error("dlsym f failed: %s\n", dlerror());
	f();
	if (*i != 2)
		error("f call failed: want i=2 got i=%d\n", *i);
	if (dlclose(h))
		error("dlclose failed: %s\n", dlerror());

	g = dlopen(0, RTLD_LAZY|RTLD_LOCAL);
	if (!g)
		error("dlopen 0 failed: %s\n", dlerror());
	i2 = dlsym(g, "i");
	s = dlerror();
	if (i2 || s == 0)
		error("dlsym i should have failed\n");
	if (dlsym(g, "main") == 0)
		error("dlsym main failed: %s\n", dlerror());

	h = dlopen("./dlopen_dso.so", RTLD_LAZY|RTLD_GLOBAL);
	i2 = dlsym(g, "i");
	if (!i2)
		error("dlsym i failed: %s\n", dlerror());
	if (*i2 != 2)
		error("want i2=2, got i2=%d\n", *i2);
	if (dlclose(g))
		error("dlclose failed: %s\n", dlerror());
	return test_status;
}
