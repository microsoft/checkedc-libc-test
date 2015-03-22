// '0' last field in an ipv6 address cannot be abbreviated to ::
#include <string.h>
#include <arpa/inet.h>
#include "test.h"

int main(void)
{
	unsigned char buf[16];
	char addr[] = "1:2:3:4:5:6:7::";

	if (inet_pton(AF_INET6, addr, buf)) {
		t_error("inet_pton(%s) returned %x:%x:%x:%x:%x:%x:%x:%x, wanted a failure\n",
			addr, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	}
	return t_status;
}
