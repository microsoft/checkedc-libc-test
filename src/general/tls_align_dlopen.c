#include <dlfcn.h>
#include "test.h"

int main()
{
	int i;
	void *h;
	struct {
		char *name;
		unsigned size;
		unsigned align;
		unsigned long addr;
	} *t;

	h = dlopen("./tls_align_dso.so", RTLD_LAZY);
	if (!h)
		error("dlopen failed\n");
	t = dlsym(h, "t");
	if (!t)
		error("dlsym failed\n");

	for (i = 0; i < 4; i++) {
		if (!t[i].name)
			error("name is not set for t[%d]\n", i);
		if (t[i].addr & (t[i].align-1))
			error("bad alignment: %s, size: %u, align: %u, addr: 0x%lx\n",
				t[i].name, t[i].size, t[i].align, t[i].addr);
	}
	return test_status;
}
