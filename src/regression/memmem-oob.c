// memmem should not access oob data
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <string.h>
#include "test.h"

int main(void)
{
	char *p = memmem("abcde", 4, "cde", 3);
	if (p)
		t_error("memmem(abcde,4,cde,3) returned %s, want NULL\n", p);
	return t_status;
}
