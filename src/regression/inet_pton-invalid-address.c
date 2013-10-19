// inet_pton should return 0 on invalid address format
#include <string.h>
#include <arpa/inet.h>
#include "test.h"

int main(void)
{
	int r;
	char addr[16];

	if ((r=inet_pton(AF_INET6, "192.168.1.1", addr)) != 0)
		t_error("inet_pton(AF_INET6, \"192.168.1.1\", addr) should return 0, got %d\n", r);
	return t_status;
}
