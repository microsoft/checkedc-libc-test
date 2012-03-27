#include "test.h"
#include <math.h>
#include <stdint.h>
#include <fenv.h>
#include <stdio.h>
#include <float.h>

static struct {
	double x;
	int n;
	double y;
} t[] = {
	0.0, 0, 0.0,
	-0.0, 0, -0.0,
	0.0, -1234567, 0.0,
	-0.0, 1234567, -0.0,
	0x1.234p0, 13, 0x1.234p13,
	0x1.234p0, -13, 0x1.234p-13,
	-0x1.234p1, 137, -0x1.234p138,
	-0x1.234p1, -137, -0x1.234p-136,
	0x1.234p1023, 1, INFINITY,
	0x1.234p1023, -1022, 0x1.234p1,
	0x1.234p1023, -1023, 0x1.234p0,
	0x1.234p1023, -1024, 0x1.234p-1,
	0x1.234p1023, -2023, 0x1.234p-1000,
	0x1.234p1023, -2045, 0x1.234p-1022,
	0x1.234p1023, -2046, 0x1.234p-1023,
	0x1.234p1023, -2048, 0x1.234p-1025,
	0x1.234p1023, -2049, 0x1.234p-1026,
	0x1p1023, -2096, 0x1p-1073,
	0x1p1023, -2097, 0x1p-1074,
	0x1p1023, -2098, 0,
	0x1.234p-1022, 1022, 0x1.234p0,
	0x1.234p-1022, 2045, 0x1.234p1023,
	0x1p-1074, 2097, 0x1p1023,
	0x1p-1074, 2098, INFINITY,
	0x1p-1074, 1, 0x1p-1073,
	0x1p-1073, -1, 0x1p-1074,
	0x1p-1074, -1, 0,
};

void test_scalbn()
{
	int i;
	double y;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		y = scalbn(t[i].x, t[i].n);
		if (y != t[i].y)
			error("scalbn(%a,%d) want %a got %a\n", t[i].x, t[i].n, t[i].y, y);
	}
}

void bench_scalbn_simple(int N)
{
	int i;
	volatile double y;

	for (i = 0; i < N; i++) {
		y = scalbn(1.25, 73);
	}
}

void bench_scalbn_hard(int N)
{
	int i;
	volatile double y;

	for (i = 0; i < N; i++) {
		y = scalbn(0x1.23p-1050, 2070);
	}
}
