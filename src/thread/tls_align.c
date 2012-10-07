#include <stddef.h>
#include "test.h"

extern struct {
	char *name;
	size_t size;
	size_t align;
	size_t addr;
} t[4];

int main()
{
	int i;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		if (!t[i].name)
			error("name is not set for t[%d]\n", i);
		if (t[i].addr & (t[i].align-1))
			error("bad alignment: %s, size: %u, align: %u, addr: 0x%lx\n",
				t[i].name, (unsigned)t[i].size, (unsigned)t[i].align, (unsigned long)t[i].addr);
	}
	return test_status;
}
