// dn_expand should accept empty name (single \0)
#define _BSD_SOURCE
#include <resolv.h>
#include "test.h"

int main(void)
{
	unsigned char packet[3] = "";
	char name[] = "x";
	int r;

	/* empty name in packet */
	r = dn_expand(packet, packet+1, packet, name, 1);
	if (r!=1)
		t_error("dn_expand(\"\", name, 1) returned %d, wanted 1\n", r);
	if (name[0])
		t_error("dn_expand(\"\", name, 1) failed: got \"%s\" name, wanted \"\"\n", name);

	/* empty name with offset pointer in packet */
	memcpy(packet, "\xc0\2", 3);
	name[0] = 'x';
	r = dn_expand(packet, packet+3, packet, name, 1);
	if (r!=2)
		t_error("dn_expand(\"\\xc0\\2\", name, 1) returned %d, wanted 1\n", r);
	if (name[0])
		t_error("dn_expand(\"\\xc0\\2\", name, 1) failed: got \"%s\" name, wanted \"\"\n", name);

	return t_status;
}
