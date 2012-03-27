#include <stdio.h>
#include <math.h>
#include "test.h"

static struct {
	float f;
	int class;
} tf[] = {
	0.0/0.0, FP_NAN,
	-0.0/0.0, FP_NAN,
	1/0.0, FP_INFINITE,
	-1/0.0, FP_INFINITE,
	0x1.ffffp127, FP_NORMAL,
	-0x1.ffffp127, FP_NORMAL,
	0x1p-127, FP_SUBNORMAL,
	-0x1p-127, FP_SUBNORMAL,
	0.0, FP_ZERO,
	-0.0, FP_ZERO,
	3.14, FP_NORMAL,
	-42, FP_NORMAL,
};
static int ntf = sizeof tf / sizeof *tf;

static struct {
	double f;
	int class;
} td[] = {
	0.0/0.0, FP_NAN,
	-0.0/0.0, FP_NAN,
	1/0.0, FP_INFINITE,
	-1/0.0, FP_INFINITE,
	0x1.ffffp1023, FP_NORMAL,
	-0x1.ffffp1023, FP_NORMAL,
	0x1p-1023, FP_SUBNORMAL,
	-0x1p-1023, FP_SUBNORMAL,
	0.0, FP_ZERO,
	-0.0, FP_ZERO,
	3.14, FP_NORMAL,
	-42, FP_NORMAL,
};
static int ntd = sizeof td / sizeof *td;

static struct {
	long double f;
	int class;
} tl[] = {
	0.0/0.0, FP_NAN,
	-0.0/0.0, FP_NAN,
	1/0.0, FP_INFINITE,
	-1/0.0, FP_INFINITE,
	0x1.ffffp16383L, FP_NORMAL,
	-0x1.ffffp16383L, FP_NORMAL,
	0x1p-16383L, FP_SUBNORMAL,
	-0x1p-16383L, FP_SUBNORMAL,
	0.0, FP_ZERO,
	-0.0, FP_ZERO,
	3.14, FP_NORMAL,
	-42, FP_NORMAL,
};
static int ntl = sizeof tl / sizeof *tl;


void test_fpclassify()
{
	int i;

	for (i = 0; i < ntf; i++) {
		if (fpclassify(tf[i].f) != tf[i].class)
			error("%a want class %d got %d\n", tf[i].f, tf[i].class, fpclassify(tf[i].f));
		if (!!isinf(tf[i].f) != (tf[i].class == FP_INFINITE))
			error("%a want class %d got isinf %d\n", tf[i].f, tf[i].class, isinf(tf[i].f));
		if (!!isnan(tf[i].f) != (tf[i].class == FP_NAN))
			error("%a want class %d got isnan %d\n", tf[i].f, tf[i].class, isnan(tf[i].f));
		if (!!isnormal(tf[i].f) != (tf[i].class == FP_NORMAL))
			error("%a want class %d got isnormal %d\n", tf[i].f, tf[i].class, isnormal(tf[i].f));
		if (!!isfinite(tf[i].f) != (tf[i].class > FP_INFINITE))
			error("%a want class %d got isfinite %d\n", tf[i].f, tf[i].class, isfinite(tf[i].f));
	}

	for (i = 0; i < ntd; i++) {
		if (fpclassify(td[i].f) != td[i].class)
			error("%a want class %d got %d\n", td[i].f, td[i].class, fpclassify(td[i].f));
		if (!!isinf(td[i].f) != (td[i].class == FP_INFINITE))
			error("%a want class %d got isinf %d\n", td[i].f, td[i].class, isinf(td[i].f));
		if (!!isnan(td[i].f) != (td[i].class == FP_NAN))
			error("%a want class %d got isnan %d\n", td[i].f, td[i].class, isnan(td[i].f));
		if (!!isnormal(td[i].f) != (td[i].class == FP_NORMAL))
			error("%a want class %d got isnormal %d\n", td[i].f, td[i].class, isnormal(td[i].f));
		if (!!isfinite(td[i].f) != (td[i].class > FP_INFINITE))
			error("%a want class %d got isfinite %d\n", td[i].f, td[i].class, isfinite(td[i].f));
	}

	for (i = 0; i < ntl; i++) {
		if (fpclassify(tl[i].f) != tl[i].class)
			error("%La want class %d got %d\n", tl[i].f, tl[i].class, fpclassify(tl[i].f));
		if (!!isinf(tl[i].f) != (tl[i].class == FP_INFINITE))
			error("%La want class %d got isinf %d\n", tl[i].f, tl[i].class, isinf(tl[i].f));
		if (!!isnan(tl[i].f) != (tl[i].class == FP_NAN))
			error("%La want class %d got isnan %d\n", tl[i].f, tl[i].class, isnan(tl[i].f));
		if (!!isnormal(tl[i].f) != (tl[i].class == FP_NORMAL))
			error("%La want class %d got isnormal %d\n", tl[i].f, tl[i].class, isnormal(tl[i].f));
		if (!!isfinite(tl[i].f) != (tl[i].class > FP_INFINITE))
			error("%La want class %d got isfinite %d\n", tl[i].f, tl[i].class, isfinite(tl[i].f));
	}
}
