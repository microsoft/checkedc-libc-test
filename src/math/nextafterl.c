#include <math.h>
#include <stdint.h>
#include <fenv.h>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include "fenvutil.h"
#include "test.h"

/* ld80 only */

static struct {
	long double x;
	long double y;
	long double z;
	int except;
} t[] = {
           0,         0,                            0, 0,
           0,      -0.0,                         -0.0, 0,
        -0.0,         0,                            0, 0,
           0,         1,                  0x1p-16445L, FE_INEXACT|FE_UNDERFLOW,
           0,        -1,                 -0x1p-16445L, FE_INEXACT|FE_UNDERFLOW,
        -0.0,         1,                  0x1p-16445L, FE_INEXACT|FE_UNDERFLOW,
        -0.0,        -1,                 -0x1p-16445L, FE_INEXACT|FE_UNDERFLOW,
 0x1p-16445L,  INFINITY,                  0x1p-16444L, FE_INEXACT|FE_UNDERFLOW,
 0x1p-16445L, -INFINITY,                            0, FE_INEXACT|FE_UNDERFLOW,
-0x1p-16445L,  INFINITY,                         -0.0, FE_INEXACT|FE_UNDERFLOW,
-0x1p-16445L, -INFINITY,                 -0x1p-16444L, FE_INEXACT|FE_UNDERFLOW,
 0x1p-16440L, -0x1p-16444L,             0x1.fp-16441L, FE_INEXACT|FE_UNDERFLOW,
 0x1p-16440L,  0x1p-16444L,             0x1.fp-16441L, FE_INEXACT|FE_UNDERFLOW,
 0x1p-16440L,  0x1p-16430L,            0x1.08p-16440L, FE_INEXACT|FE_UNDERFLOW,
    LDBL_MIN,         0, 0x1.fffffffffffffffcp-16383L, FE_INEXACT|FE_UNDERFLOW,
   -LDBL_MIN,         0,-0x1.fffffffffffffffcp-16383L, FE_INEXACT|FE_UNDERFLOW,
 0x1.fffffffffffffffcp-16383L,  1,           LDBL_MIN, 0,
-0x1.fffffffffffffffcp-16383L, -1,          -LDBL_MIN, 0,
           1,         2,     0x1.0000000000000002p+0L, 0,
           1,        -2,     0x1.fffffffffffffffep-1L, 0,
           1,       0.5,     0x1.fffffffffffffffep-1L, 0,
    0x1p1023,  0x1p1000,  0x1.fffffffffffffffep+1022L, 0,
    0x1p1023,  INFINITY,  0x1.0000000000000002p+1023L, 0,
        -1.5,      -2.5,    -0x1.8000000000000002p+0L, 0,
        -1.5,       2.5,    -0x1.7ffffffffffffffep+0L, 0,
         1.5,      -2.5,     0x1.7ffffffffffffffep+0L, 0,
    LDBL_MAX,  INFINITY,                     INFINITY, FE_INEXACT|FE_OVERFLOW,
    INFINITY,  INFINITY,                     INFINITY, 0,
   -LDBL_MAX, -INFINITY,                    -INFINITY, FE_INEXACT|FE_OVERFLOW,
   -INFINITY, -INFINITY,                    -INFINITY, 0,
         NAN,         1,                          NAN, 0,
           1,       NAN,                          NAN, 0,
};

void test_nextafterl()
{
	int f, i;
	long double z;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		feclearexcept(FE_ALL_EXCEPT);
		z = nextafterl(t[i].x, t[i].y);
		f = fetestexcept(FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW|FE_UNDERFLOW|FE_INEXACT);

		if (z != t[i].z && !(isnan(z) && isnan(t[i].z)))
			error("%d nextafterl(%La, %La) want %La got %La\n", i, t[i].x, t[i].y, t[i].z, z);
		if (f != t[i].except)
			error("%d nextafterl(%La, %La)==%La want except=%s got except=%s\n",
				i, t[i].x, t[i].y, t[i].z, strdup(strexcept(t[i].except)), strdup(strexcept(f)));
	}
}

void bench_nextafterl_normal(int N)
{
	int i;
	volatile long double z;

	for (i = 0; i < N; i++) {
		z = nextafterl(1.25, 4);
	}
}

void bench_nextafterl_subnormal(int N)
{
	int i;
	volatile long double z;

	for (i = 0; i < N; i++) {
		z = nextafterl(0x1p-16440L, -0x1p-16444L);
	}
}
