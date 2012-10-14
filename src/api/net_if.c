#include <net/if.h>
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
{
struct if_nameindex x;
F(unsigned, if_index)
F(char*, if_name)
}
C(IF_NAMESIZE)
void(*p_if_freenameindex)(struct if_nameindex*) = if_freenameindex;
char*(*p_if_indextoname)(unsigned,char*) = if_indextoname;
struct if_nameindex*(*p_if_nameindex)(void) = if_nameindex;
unsigned(*p_if_nametoindex)(const char*) = if_nametoindex;
}
