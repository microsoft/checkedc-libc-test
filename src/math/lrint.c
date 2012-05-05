#include "test.h"
#include <math.h>
#include <stdint.h>
#include <fenv.h>
#include <stdio.h>
#include <float.h>
#include "fenvutil.h"

static struct {
	int round;
	double x;
	long n;
	int except;
} t[] = {
FE_TONEAREST,             0x0p+0,           0, 0,
FE_DOWNWARD,              0x0p+0,           0, 0,
FE_UPWARD,                0x0p+0,           0, 0,
FE_TOWARDZERO,            0x0p+0,           0, 0,
FE_TONEAREST,             0x1p-2,           0, FE_INEXACT,
FE_DOWNWARD,              0x1p-2,           0, FE_INEXACT,
FE_UPWARD,                0x1p-2,           1, FE_INEXACT,
FE_TOWARDZERO,            0x1p-2,           0, FE_INEXACT,
FE_TONEAREST,            -0x1p-2,           0, FE_INEXACT,
FE_DOWNWARD,             -0x1p-2,          -1, FE_INEXACT,
FE_UPWARD,               -0x1p-2,           0, FE_INEXACT,
FE_TOWARDZERO,           -0x1p-2,           0, FE_INEXACT,
FE_TONEAREST,             0x1p-1,           0, FE_INEXACT,
FE_DOWNWARD,              0x1p-1,           0, FE_INEXACT,
FE_UPWARD,                0x1p-1,           1, FE_INEXACT,
FE_TOWARDZERO,            0x1p-1,           0, FE_INEXACT,
FE_TONEAREST,            -0x1p-1,           0, FE_INEXACT,
FE_DOWNWARD,             -0x1p-1,          -1, FE_INEXACT,
FE_UPWARD,               -0x1p-1,           0, FE_INEXACT,
FE_TOWARDZERO,           -0x1p-1,           0, FE_INEXACT,
FE_TONEAREST,           0x1.8p-1,           1, FE_INEXACT,
FE_DOWNWARD,            0x1.8p-1,           0, FE_INEXACT,
FE_UPWARD,              0x1.8p-1,           1, FE_INEXACT,
FE_TOWARDZERO,          0x1.8p-1,           0, FE_INEXACT,
FE_TONEAREST,          -0x1.8p-1,          -1, FE_INEXACT,
FE_DOWNWARD,           -0x1.8p-1,          -1, FE_INEXACT,
FE_UPWARD,             -0x1.8p-1,           0, FE_INEXACT,
FE_TOWARDZERO,         -0x1.8p-1,           0, FE_INEXACT,
FE_TONEAREST,             0x1p+0,           1, 0,
FE_DOWNWARD,              0x1p+0,           1, 0,
FE_UPWARD,                0x1p+0,           1, 0,
FE_TOWARDZERO,            0x1p+0,           1, 0,
FE_TONEAREST,            -0x1p+0,          -1, 0,
FE_DOWNWARD,             -0x1p+0,          -1, 0,
FE_UPWARD,               -0x1p+0,          -1, 0,
FE_TOWARDZERO,           -0x1p+0,          -1, 0,
FE_TONEAREST,           0x1.4p+0,           1, FE_INEXACT,
FE_DOWNWARD,            0x1.4p+0,           1, FE_INEXACT,
FE_UPWARD,              0x1.4p+0,           2, FE_INEXACT,
FE_TOWARDZERO,          0x1.4p+0,           1, FE_INEXACT,
FE_TONEAREST,          -0x1.4p+0,          -1, FE_INEXACT,
FE_DOWNWARD,           -0x1.4p+0,          -2, FE_INEXACT,
FE_UPWARD,             -0x1.4p+0,          -1, FE_INEXACT,
FE_TOWARDZERO,         -0x1.4p+0,          -1, FE_INEXACT,
FE_TONEAREST,            0x1p+30,  1073741824, 0,
FE_DOWNWARD,             0x1p+30,  1073741824, 0,
FE_UPWARD,               0x1p+30,  1073741824, 0,
FE_TOWARDZERO,           0x1p+30,  1073741824, 0,
FE_TONEAREST,           -0x1p+30, -1073741824, 0,
FE_DOWNWARD,            -0x1p+30, -1073741824, 0,
FE_UPWARD,              -0x1p+30, -1073741824, 0,
FE_TOWARDZERO,          -0x1p+30, -1073741824, 0,
FE_TONEAREST,   0x1.fffffffcp+30,  2147483647, 0,
FE_DOWNWARD,    0x1.fffffffcp+30,  2147483647, 0,
FE_UPWARD,      0x1.fffffffcp+30,  2147483647, 0,
FE_TOWARDZERO,  0x1.fffffffcp+30,  2147483647, 0,
FE_TONEAREST,  -0x1.fffffffcp+30, -2147483647, 0,
FE_DOWNWARD,   -0x1.fffffffcp+30, -2147483647, 0,
FE_UPWARD,     -0x1.fffffffcp+30, -2147483647, 0,
FE_TOWARDZERO, -0x1.fffffffcp+30, -2147483647, 0,
FE_TONEAREST,            0x1p+31,           0, FE_INVALID,
FE_DOWNWARD,             0x1p+31,           0, FE_INVALID,
FE_UPWARD,               0x1p+31,           0, FE_INVALID,
FE_TOWARDZERO,           0x1p+31,           0, FE_INVALID,
FE_TONEAREST,           -0x1p+31, -2147483648, 0,
FE_DOWNWARD,            -0x1p+31, -2147483648, 0,
FE_UPWARD,              -0x1p+31, -2147483648, 0,
FE_TOWARDZERO,          -0x1p+31, -2147483648, 0,
FE_TONEAREST,   0x1.00000002p+31,           0, FE_INVALID,
FE_DOWNWARD,    0x1.00000002p+31,           0, FE_INVALID,
FE_UPWARD,      0x1.00000002p+31,           0, FE_INVALID,
FE_TOWARDZERO,  0x1.00000002p+31,           0, FE_INVALID,
FE_TONEAREST,  -0x1.00000002p+31,           0, FE_INVALID,
FE_DOWNWARD,   -0x1.00000002p+31,           0, FE_INVALID,
FE_UPWARD,     -0x1.00000002p+31,           0, FE_INVALID,
FE_TOWARDZERO, -0x1.00000002p+31,           0, FE_INVALID,
FE_TONEAREST,   0x1.fffffffep+30,           0, FE_INVALID,
FE_DOWNWARD,    0x1.fffffffep+30,  2147483647, FE_INEXACT,
FE_UPWARD,      0x1.fffffffep+30,           0, FE_INVALID,
FE_TOWARDZERO,  0x1.fffffffep+30,  2147483647, FE_INEXACT,
FE_TONEAREST,  -0x1.fffffffep+30, -2147483648, FE_INEXACT,
FE_DOWNWARD,   -0x1.fffffffep+30, -2147483648, FE_INEXACT,
FE_UPWARD,     -0x1.fffffffep+30, -2147483647, FE_INEXACT,
FE_TOWARDZERO, -0x1.fffffffep+30, -2147483647, FE_INEXACT,
FE_TONEAREST,   0x1.00000001p+31,           0, FE_INVALID,
FE_DOWNWARD,    0x1.00000001p+31,           0, FE_INVALID,
FE_UPWARD,      0x1.00000001p+31,           0, FE_INVALID,
FE_TOWARDZERO,  0x1.00000001p+31,           0, FE_INVALID,
FE_TONEAREST,  -0x1.00000001p+31, -2147483648, FE_INEXACT,
FE_DOWNWARD,   -0x1.00000001p+31,           0, FE_INVALID,
FE_UPWARD,     -0x1.00000001p+31, -2147483648, FE_INEXACT,
FE_TOWARDZERO, -0x1.00000001p+31, -2147483648, FE_INEXACT,
FE_TONEAREST,            0x1p+32,           0, FE_INVALID,
FE_DOWNWARD,             0x1p+32,           0, FE_INVALID,
FE_UPWARD,               0x1p+32,           0, FE_INVALID,
FE_TOWARDZERO,           0x1p+32,           0, FE_INVALID,
FE_TONEAREST,           -0x1p+32,           0, FE_INVALID,
FE_DOWNWARD,            -0x1p+32,           0, FE_INVALID,
FE_UPWARD,              -0x1p+32,           0, FE_INVALID,
FE_TOWARDZERO,          -0x1p+32,           0, FE_INVALID,
FE_TONEAREST,   0x1.ffffffffp+31,           0, FE_INVALID,
FE_DOWNWARD,    0x1.ffffffffp+31,           0, FE_INVALID,
FE_UPWARD,      0x1.ffffffffp+31,           0, FE_INVALID,
FE_TOWARDZERO,  0x1.ffffffffp+31,           0, FE_INVALID,
FE_TONEAREST,  -0x1.ffffffffp+31,           0, FE_INVALID,
FE_DOWNWARD,   -0x1.ffffffffp+31,           0, FE_INVALID,
FE_UPWARD,     -0x1.ffffffffp+31,           0, FE_INVALID,
FE_TOWARDZERO, -0x1.ffffffffp+31,           0, FE_INVALID,
};

void test_lrint()
{
	int f, i;
	long n;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		fesetround(t[i].round);
		feclearexcept(FE_ALL_EXCEPT);
		n = lrint(t[i].x);
		f = fetestexcept(FE_ALL_EXCEPT);

		if (t[i].except != FE_INVALID && n != t[i].n)
			error("round=%s, lrint(%a) want %ld got %ld\n", strround(t[i].round), t[i].x, t[i].n, n);
		if (f != t[i].except)
			error("round=%s, lrint(%a)==%ld want except=%s, got except=%s\n",
				strround(t[i].round), t[i].x, t[i].n, strdup(strexcept(t[i].except)), strdup(strexcept(f)));
	}
}

void bench_lrint_simple(int N)
{
	int i;
	volatile int n;

	for (i = 0; i < N; i++) {
		n = lrint(1.25);
	}
}

void bench_lrint_hard(int N)
{
	int i;
	volatile int n;

	for (i = 0; i < N; i++) {
//		feclearexcept(FE_ALL_EXCEPT);
//		n = lrint(1.5);
//		n = lrint(0x1p32);
//		n = lrint(-0x1p31);
		n = lrint(0x1p31+0.5);
	}
}
