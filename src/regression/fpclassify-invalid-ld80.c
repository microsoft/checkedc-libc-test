// commit: f657fe4b9f734d7fdea515af8dffbf7c28ce4fbc 2013-09-05
// classify invalid x86 ld80 representations (this is ub, we follow the fpu)
#include <math.h>
#include <float.h>
#include <stdint.h>
#include "test.h"

#if LDBL_MANT_DIG==64
static char *strclass(int c)
{
#define C(n) case n: return #n;
	switch (c) {
	C(FP_NAN)
	C(FP_INFINITE)
	C(FP_ZERO)
	C(FP_SUBNORMAL)
	C(FP_NORMAL)
	}
	return "invalid";
}

#define T(desc,got,want) do{ \
if (got!=want) t_error("fpclassify(%s) failed: got %s want %s\n", desc, strclass(got), #want); \
}while(0)

int main(void)
{
	union {
		long double f;
		struct {
			uint64_t m;
			uint16_t se;
		} i;
	} u;
	int c;

	u.f = 0;
	u.i.m = (uint64_t)1<<63;
	c = fpclassify(u.f);
	T("zero with msb set", c, FP_NORMAL);
	u.i.m++;
	c = fpclassify(u.f);
	T("subnormal with msb set", c, FP_NORMAL);
	u.f=1;
	u.i.m=0;
	c = fpclassify(u.f);
	T("normal with msb unset", c, FP_NAN);
	u.f=INFINITY;
	u.i.m=0;
	c = fpclassify(u.f);
	T("infinity with msb unset", c, FP_NAN);
	u.f=NAN;
	u.i.m&=(uint64_t)-1/2;
	c = fpclassify(u.f);
	T("nan with msb unset", c, FP_NAN);
	return t_status;
}
#else
int main(void)
{
	return 0;
}
#endif
