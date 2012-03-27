#include "test.h"
#include <math.h>
#include <stdint.h>
#include <fenv.h>
#include <stdio.h>
#include <float.h>


void test_fenv()
{
	int r;

	r = fesetround(FE_UPWARD);
	if (r != 0)
		error("fesetround %d\n", r);
	r = fegetround();
	if (r != FE_UPWARD)
		error("fegetround %x wanted %x\n", r, FE_UPWARD);
	r = fesetround(FE_TONEAREST);
	if (r != 0)
		error("fesetround %d\n", r);
	r = fegetround();
	if (r != FE_TONEAREST)
		error("fegetround %x wanted %x\n", r, FE_TONEAREST);
}

void test_fenv_except()
{
	int i,r;

	for (i = 0; i < 64; i++) {
		feclearexcept(FE_ALL_EXCEPT);

		r = feraiseexcept(i);
		if (r)
			error("feraise %d returned %d\n", i, r);
		r = fetestexcept(FE_ALL_EXCEPT);
		if (r != i)
			error("feraise want %d got %d\n", i, r);
	}
}

void bench_feraiseexcept(int N)
{
	int i;
	for (i = 0; i < N; i++) {
		feraiseexcept(i&63);
	}
}

void bench_fesetround(int N)
{
	int i;
	int r = 0;

	for (i = 0; i < N; i++) {
		r ^= 0x400;
		fesetround(r);
	}
}
