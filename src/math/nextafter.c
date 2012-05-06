#include <math.h>
#include <stdint.h>
#include <fenv.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "fenvutil.h"
#include "test.h"

static struct {
	double x;
	double y;
	double z;
	int except;
} t[] = {
         0,         0,                        0, 0,
         0,      -0.0,                     -0.0, 0,
      -0.0,         0,                        0, 0,
         0,         1,                0x1p-1074, FE_INEXACT|FE_UNDERFLOW,
         0,        -1,               -0x1p-1074, FE_INEXACT|FE_UNDERFLOW,
      -0.0,         1,                0x1p-1074, FE_INEXACT|FE_UNDERFLOW,
      -0.0,        -1,               -0x1p-1074, FE_INEXACT|FE_UNDERFLOW,
 0x1p-1074,  INFINITY,                0x1p-1073, FE_INEXACT|FE_UNDERFLOW,
 0x1p-1074, -INFINITY,                        0, FE_INEXACT|FE_UNDERFLOW,
-0x1p-1074,  INFINITY,                     -0.0, FE_INEXACT|FE_UNDERFLOW,
-0x1p-1074, -INFINITY,               -0x1p-1073, FE_INEXACT|FE_UNDERFLOW,
   DBL_MIN,         0,  0x0.fffffffffffffp-1022, FE_INEXACT|FE_UNDERFLOW,
  -DBL_MIN,         0, -0x0.fffffffffffffp-1022, FE_INEXACT|FE_UNDERFLOW,
         1,         2,     0x1.0000000000001p+0, 0,
         1,        -2,     0x1.fffffffffffffp-1, 0,
         1,       0.5,     0x1.fffffffffffffp-1, 0,
  0x1p1023,  0x1p1000,  0x1.fffffffffffffp+1022, 0,
  0x1p1023,  INFINITY,  0x1.0000000000001p+1023, 0,
      -1.5,      -2.5,    -0x1.8000000000001p+0, 0,
      -1.5,       2.5,    -0x1.7ffffffffffffp+0, 0,
       1.5,      -2.5,     0x1.7ffffffffffffp+0, 0,
   DBL_MAX,  INFINITY,                 INFINITY, FE_INEXACT|FE_OVERFLOW,
  INFINITY,  INFINITY,                 INFINITY, 0,
  -DBL_MAX, -INFINITY,                -INFINITY, FE_INEXACT|FE_OVERFLOW,
 -INFINITY, -INFINITY,                -INFINITY, 0,
       NAN,         1,                      NAN, 0,
         1,       NAN,                      NAN, 0,
};

void test_nextafter()
{
	int f, i;
	double z;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		feclearexcept(FE_ALL_EXCEPT);
		z = nextafter(t[i].x, t[i].y);
		f = fetestexcept(FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW|FE_UNDERFLOW|FE_INEXACT);

		if (z != t[i].z && !(isnan(z) && isnan(t[i].z)))
			error("nextafter(%a, %a) want %a got %a\n", t[i].x, t[i].y, t[i].z, z);
		if (f != t[i].except)
			error("nextafter(%a, %a)==%a want except=%s got except=%s\n",
				t[i].x, t[i].y, t[i].z, strdup(strexcept(t[i].except)), strdup(strexcept(f)));
	}
}

void bench_nextafter_normal(int N)
{
	int i;
	volatile double z;

	for (i = 0; i < N; i++) {
		z = nextafter(1.25, 4);
	}
}

void bench_nextafter_subnormal(int N)
{
	int i;
	volatile double z;

	for (i = 0; i < N; i++) {
		z = nextafter(0x1p-1070, -0x1p-1071);
	}
}
