#include "test.h"
#include <math.h>
#include <stdint.h>
#include <fenv.h>
#include <stdio.h>
#include <float.h>

static struct {
	int flag;
	char *s;
} eflags[] = {
	{FE_INVALID, "FE_INVALID"},
	{FE_DIVBYZERO, "FE_DIVBYZERO"},
	{FE_OVERFLOW, "FE_OVERFLOW"},
	{FE_UNDERFLOW, "FE_UNDERFLOW"},
	{FE_INEXACT, "FE_INEXACT"},
};
static int ne = sizeof eflags / sizeof *eflags;

static struct {
	int flag;
	char *s;
} rflags[] = {
	{FE_TONEAREST,"FE_TONEAREST,"},
	{FE_DOWNWARD,"FE_DOWNWARD,"},
	{FE_UPWARD,"FE_UPWARD,"},
	{FE_TOWARDZERO,"FE_TOWARDZERO,"},
};
static int nr = sizeof rflags / sizeof *rflags;

void printexcept(int f) {
	int i, all=0;

	for (i = 0; i < ne; i++)
		if (f & eflags[i].flag) {
			printf("%s%s", all ? "|" : "", eflags[i].s);
			all |= eflags[i].flag;
		}
	if (all != f) {
		printf("%s%d", all ? "|" : "", f & ~all);
		all = f;
	}
	printf("%s,", all ? "" : "0");
}

void printround(int f) {
	int i;

	for (i = 0; i < nr; i++)
		if (f == rflags[i].flag) {
			printf("%s ", rflags[i].s);
			return;
		}
	printf("%d, ", f);
}

/*
struct {double x;} t[] = {
0.0,
0.25,
-0.25,
0.5,
-0.5,
0.75,
-0.75,
1.0,
-1.0,
1.25,
-1.25,
0x1p30,
-0x1p30,
0x1p31-1,
-0x1p31+1,
0x1p31,
-0x1p31,
0x1p31+1,
-0x1p31-1,
0x1p31-0.5,
-0x1p31+0.5,
0x1p31+0.5,
-0x1p31-0.5,
0x1p32,
-0x1p32,
0x1p32 - 0.5,
-0x1p32 + 0.5,
};

void test_gendata()
{
	int f, i, j;
	long n;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		for (j = 0; j < nr; j++) {
			fesetround(rflags[j].flag);
			feclearexcept(FE_ALL_EXCEPT);
			n = lrint(t[i].x);
			f = fetestexcept(FE_ALL_EXCEPT);
			if (f == FE_INVALID)
				n = 0;

			printround(rflags[j].flag);
			printf("%18a, %11ld, ", t[i].x, n);
			printexcept(f);
			printf("\n");
		}
	}
}
*/

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

		if (t[i].except != FE_INVALID && n != t[i].n) {
			error("round=");
			printround(t[i].round);
			printf("lrint(%a) want %ld got %ld\n", t[i].x, t[i].n, n);
		}
		if (f != t[i].except) {
			error("round=");
			printround(t[i].round);
			printf("lrint(%a)==%ld want except=", t[i].x, t[i].n);
			printexcept(t[i].except);
			printf(" got except=");
			printexcept(f);
			printf("\n");
		}
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
