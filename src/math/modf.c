#include <stdio.h>
#include <math.h>
#include "test.h"

static struct {
	double x;
	double yf;
	double yi;
} t[] = {
	0.7, 0x1.6666666666666p-1, 0.0,
	-0.7, -0x1.6666666666666p-1, -0.0,
	1.7, 0x1.6666666666666p-1, 1.0,
	-1.7, -0x1.6666666666666p-1, -1.0,
	2.0, 0.0, 2.0,
	-2.0, -0.0, -2.0,
	-0x1p99, -0.0, -0x1p99,
	-0.0, -0.0, -0.0,
	INFINITY, 0.0, INFINITY,
	-INFINITY, -0.0, -INFINITY,
	NAN, NAN, NAN,
};

static struct {
	float x;
	float yf;
	float yi;
} tf[] = {
	0.7, 0x1.666666p-1, 0.0,
	-0.7, -0x1.666666p-1, -0.0,
	1.7, 0x1.666668p-1, 1.0,
	-1.7, -0x1.666668p-1, -1.0,
	2.0, 0.0, 2.0,
	-2.0, -0.0, -2.0,
	-0x1p99, -0.0, -0x1p99,
	-0.0, -0.0, -0.0,
	INFINITY, 0.0, INFINITY,
	-INFINITY, -0.0, -INFINITY,
	NAN, NAN, NAN,
};

static struct {
	long double x;
	long double yf;
	long double yi;
} tl[] = {
	0.7L, 0x1.6666666666666666p-1L, 0.0,
	-0.7L, -0x1.6666666666666666p-1L, -0.0,
	1.7L, 0x1.6666666666666668p-1L, 1.0,
	-1.7L, -0x1.6666666666666668p-1L, -1.0,
	2.0, 0, 2.0,
	-2.0, -0.0, -2.0,
	-0x1p99, -0.0, -0x1p99,
	-0.0, -0.0, -0.0,
	INFINITY, 0.0, INFINITY,
	-INFINITY, -0.0, -INFINITY,
	NAN, NAN, NAN,
};

#define eq(a, b) (isnan(a) && isnan(b) || ((a) == (b) && signbit(a) == signbit(b)))

void test_modf()
{
	double yf, yi;
	int i;
	for (i = 0; i < sizeof t/sizeof *t; i++) {
		yf = modf(t[i].x, &yi);
		if (!eq(yf,t[i].yf) || !eq(yi,t[i].yi))
			error("modf(%a) want %a %a got %a %a\n", t[i].x, t[i].yf, t[i].yi, yf, yi);
	}
}
void test_modff()
{
	float yf, yi;
	int i;
	for (i = 0; i < sizeof tf/sizeof *tf; i++) {
		yf = modff(tf[i].x, &yi);
		if (!eq(yf,tf[i].yf) || !eq(yi,tf[i].yi))
			error("modff(%a) want %a %a got %a %a\n", tf[i].x, tf[i].yf, tf[i].yi, yf, yi);
	}
}
void test_modfl()
{
	long double yf, yi;
	int i;
	for (i = 0; i < sizeof tl/sizeof *tl; i++) {
		yf = modfl(tl[i].x, &yi);
		if (!eq(yf,tl[i].yf) || !eq(yi,tl[i].yi))
			error("modfl(%La) want %La %La got %La %La\n", tl[i].x, tl[i].yf, tl[i].yi, yf, yi);
	}
}

void bench_modf_small(int N)
{
	int i;
	volatile double yf, yi;

	for (i = 0; i < N; i++)
		yf = modf(1234.5678, &yi);
}

void bench_modf_large(int N)
{
	int i;
	volatile double yf, yi;

	for (i = 0; i < N; i++)
		yf = modf(1.2345678e300, &yi);
}
