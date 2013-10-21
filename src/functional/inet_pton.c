// inet_pton and inet_ntop tests with roundtrip check
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "test.h"

static int digit(int c)
{
	c-='0';
	if (c>9) c-='a'-'0'-10;
	return c;
}

static void tobin(char *d, char *s)
{
	int i;
	for (i=0; s[2*i]; i++) d[i] = digit(s[2*i])*16+digit(s[2*i+1]);
}

static void tohex(char *d, char *s, int n)
{
	int i;
	for (i=0; i<n; i++) sprintf(d+2*i, "%02x", (unsigned char)s[i]);
}

#define T(af,src,ret,hex) do{\
	int r; \
	char binaddr[16]; \
	char hexaddr[40]; \
	char txtaddr[60]; \
	r=inet_pton(af,src,binaddr); \
	if (r!=ret) \
		t_error("inet_pton("#af", "#src", addr) returned %d, want %d\n", r, ret); \
	if (ret!=1) break; \
	tohex(hexaddr,binaddr,af==AF_INET?4:16); \
	if (strcmp(hexaddr,hex)) \
		t_error("inet_pton("#af", "#src", addr) got addr %s, want %s\n", hexaddr, hex); \
	tobin(binaddr,hex); \
	if (inet_ntop(af,binaddr,txtaddr,sizeof txtaddr)!=txtaddr) \
		t_error("inet_ntop("#af", <"#hex">, buf, size) did not return buf\n"); \
	if (af==AF_INET && strcmp(txtaddr,src)) \
		t_error("inet_ntop("#af", <"#hex">, buf, size) got %s, want %s\n", txtaddr, src); \
	if (af!=AF_INET6) break; \
	if (inet_pton(af,txtaddr,binaddr)!=1) \
		t_error("inet_ntop("#af", <"#hex">, buf, size) got %s, it is rejected by inet_pton\n", txtaddr); \
	tohex(hexaddr,binaddr,16); \
	if (strcmp(hexaddr,hex)) \
		t_error("inet_ntop("#af", <"#hex">, buf, size) got %s that is %s, want %s\n", txtaddr, hexaddr, hex); \
	if (strncmp(hex,"00000000000000000000ffff",24)==0 && !strchr(txtaddr,'.')) \
		t_error("inet_ntop("#af", <"#hex">, buf, size) got %s, should be ipv4 mapped\n", txtaddr); \
}while(0);

int main(void)
{
T(AF_INET+AF_INET6, "0.0.0.0", -1, "")
T(AF_INET, "0.0.0.0", 1, "00000000")
T(AF_INET, "127.0.0.1", 1, "7f000001")
T(AF_INET, "255.255.255.255", 1, "ffffffff")
T(AF_INET, "1.2.3.", 0, "")
T(AF_INET, "1.2.3.4.5", 0, "")
T(AF_INET, ".1.2.3", 0, "")
T(AF_INET, "1.2.03.4", 0, "")
T(AF_INET, "1.2.3.a", 0, "")
T(AF_INET, "1.256.2.3", 0, "")
T(AF_INET, "1.2.4294967296.3", 0, "")
T(AF_INET, "1.2.-4294967295.3", 0, "")
T(AF_INET, "1.2. 3.4", 0, "")
T(AF_INET6, ":", 0, "")
T(AF_INET6, "::", 1, "00000000000000000000000000000000")
T(AF_INET6, "::1", 1, "00000000000000000000000000000001")
T(AF_INET6, ":::", 0, "")
T(AF_INET6, "192.168.1.1", 0, "")
T(AF_INET6, ":192.168.1.1", 0, "")
T(AF_INET6, "::192.168.1.1", 1, "000000000000000000000000c0a80101")
T(AF_INET6, ":ffff:192.168.1.1", 0, "")
T(AF_INET6, "::ffff:192.168.1.1", 1, "00000000000000000000ffffc0a80101")
T(AF_INET6, ".192.168.1.1", 0, "")
T(AF_INET6, ":.192.168.1.1", 0, "")
T(AF_INET6, "a:0b:00c:000d:0000e:f::", 1, "000a000b000c000d000e000f00000000")
T(AF_INET6, "ffff:c0a8:5e4", 0, "")
T(AF_INET6, ":ffff:c0a8:5e4", 0, "")
T(AF_INET6, "0:0:0:0:0:ffff:c0a8:5e4", 1, "00000000000000000000ffffc0a805e4")
T(AF_INET6, "0:0:0:0:ffff:c0a8:5e4", 0, "")
T(AF_INET6, "0::ffff:c0a8:5e4", 1, "00000000000000000000ffffc0a805e4")
T(AF_INET6, "::0::ffff:c0a8:5e4", 0, "")
T(AF_INET6, "c0a8", 0, "")
return t_status;
}
