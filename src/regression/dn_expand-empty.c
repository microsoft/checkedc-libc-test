// dn_expand should accept empty name (single \0)
#include <resolv.h>
#include "test.h"

int main(void)
{
	unsigned char packet[] = "";
	char name[] = "x";
	int r;
	r = dn_expand(packet, packet+1, packet, name, 1);
	if (r!=1)
		t_error("__dn_expand(\"\") returned %d, wanted 1\n", r);
	if (*name)
		t_error("__dn_expand(\"\") failed: got \"%s\" wanted \"\"\n", name);
	return t_status;
}
