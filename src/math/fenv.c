#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "util.h"

static int test_status;

#define error(...) print(__FILE__, __LINE__, __VA_ARGS__)
static void print(char *f, int l, char *fmt, ...)
{
	test_status = 1;
	va_list ap;
	printf("%s:%d: ", f, l);
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
}

#define F(n) {#n, n}

static struct {
	char *name;
	int i;
} te[] = {
#ifdef FE_DIVBYZERO
	F(FE_DIVBYZERO),
#endif
#ifdef FE_INEXACT
	F(FE_INEXACT),
#endif
#ifdef FE_INVALID
	F(FE_INVALID),
#endif
#ifdef FE_OVERFLOW
	F(FE_OVERFLOW),
#endif
#ifdef FE_UNDERFLOW
	F(FE_UNDERFLOW),
#endif
};

static void test_except()
{
	#pragma STDC FENV_ACCESS ON
	int i,r;

	for (i=0; i < sizeof te/sizeof*te; i++) {
		feclearexcept(FE_ALL_EXCEPT);

		r = feraiseexcept(te[i].i);
		if (r)
			error("feraiseexcept(%s) returned %d\n", te[i].name, r);
		r = fetestexcept(FE_ALL_EXCEPT);
		if (r != te[i].i)
			error("feraiseexcept(%s) want %d got %d\n",
				te[i].name, te[i].i, r);
	}
}

static struct {
	char *name;
	int i;
} tr[] = {
	F(FE_TONEAREST),
#ifdef FE_UPWARD
	F(FE_UPWARD),
#endif
#ifdef FE_DOWNWARD
	F(FE_DOWNWARD),
#endif
#ifdef FE_TOWARDZERO
	F(FE_TOWARDZERO),
#endif
};

static void test_round()
{
	#pragma STDC FENV_ACCESS ON
	int i,r;

	for (i=0; i < sizeof tr/sizeof*tr; i++) {
		if (tr[i].i < 0)
			error("%s (%d) < 0\n", tr[i].name, tr[i].i);
		for (r=0; r < i; r++)
			if (tr[r].i == tr[i].i)
				error("%s (%d) == %s (%d)\n",
					tr[r].name, tr[r].i, tr[i].name, tr[i].i);
	}

	for (i=0; i < sizeof tr/sizeof*tr; i++) {
		r = fesetround(tr[i].i);
		if (r != 0)
			error("fesetround %d\n", r);
		r = fegetround();
		if (r != tr[i].i)
			error("fegetround %x wanted %x\n", r, tr[i].i);
	}
}

/* ieee double precision add operation */
static struct dd_d t[] = {
T(RN,                  0x1p+0,                 0x1p-52,    0x1.0000000000001p+0,          0x0p+0, 0)
T(RN,                  0x1p+0,                 0x1p-53,                  0x1p+0,         -0x1p-1, INEXACT)
T(RN,                  0x1p+0,              0x1.01p-53,    0x1.0000000000001p+0,       0x1.fep-2, INEXACT)
T(RN,                  0x1p+0,                -0x1p-54,                  0x1p+0,          0x1p-2, INEXACT)
T(RN,                  0x1p+0,             -0x1.01p-54,    0x1.fffffffffffffp-1,      -0x1.fep-2, INEXACT)
T(RN,                 -0x1p+0,                -0x1p-53,                 -0x1p+0,          0x1p-1, INEXACT)
T(RN,                 -0x1p+0,             -0x1.01p-53,   -0x1.0000000000001p+0,      -0x1.fep-2, INEXACT)
T(RN,                 -0x1p+0,                 0x1p-54,                 -0x1p+0,         -0x1p-2, INEXACT)
T(RN,                 -0x1p+0,              0x1.01p-54,   -0x1.fffffffffffffp-1,       0x1.fep-2, INEXACT)

T(RU,                  0x1p+0,                 0x1p-52,    0x1.0000000000001p+0,          0x0p+0, 0)
T(RU,                  0x1p+0,                 0x1p-53,    0x1.0000000000001p+0,          0x1p-1, INEXACT)
T(RU,                  0x1p+0,              0x1.01p-53,    0x1.0000000000001p+0,       0x1.fep-2, INEXACT)
T(RU,                  0x1p+0,                -0x1p-54,                  0x1p+0,          0x1p-2, INEXACT)
T(RU,                  0x1p+0,             -0x1.01p-54,                  0x1p+0,       0x1.01p-2, INEXACT)
T(RU,                 -0x1p+0,                -0x1p-53,                 -0x1p+0,          0x1p-1, INEXACT)
T(RU,                 -0x1p+0,             -0x1.01p-53,                 -0x1p+0,       0x1.01p-1, INEXACT)
T(RU,                 -0x1p+0,                 0x1p-54,   -0x1.fffffffffffffp-1,          0x1p-1, INEXACT)
T(RU,                 -0x1p+0,              0x1.01p-54,   -0x1.fffffffffffffp-1,       0x1.fep-2, INEXACT)

T(RD,                  0x1p+0,                 0x1p-52,    0x1.0000000000001p+0,          0x0p+0, 0)
T(RD,                  0x1p+0,                 0x1p-53,                  0x1p+0,         -0x1p-1, INEXACT)
T(RD,                  0x1p+0,              0x1.01p-53,                  0x1p+0,      -0x1.01p-1, INEXACT)
T(RD,                  0x1p+0,                -0x1p-54,    0x1.fffffffffffffp-1,         -0x1p-1, INEXACT)
T(RD,                  0x1p+0,             -0x1.01p-54,    0x1.fffffffffffffp-1,      -0x1.fep-2, INEXACT)
T(RD,                 -0x1p+0,                -0x1p-53,   -0x1.0000000000001p+0,         -0x1p-1, INEXACT)
T(RD,                 -0x1p+0,             -0x1.01p-53,   -0x1.0000000000001p+0,      -0x1.fep-2, INEXACT)
T(RD,                 -0x1p+0,                 0x1p-54,                 -0x1p+0,         -0x1p-2, INEXACT)
T(RD,                 -0x1p+0,              0x1.01p-54,                 -0x1p+0,      -0x1.01p-2, INEXACT)

T(RZ,                  0x1p+0,                 0x1p-52,    0x1.0000000000001p+0,          0x0p+0, 0)
T(RZ,                  0x1p+0,                 0x1p-53,                  0x1p+0,         -0x1p-1, INEXACT)
T(RZ,                  0x1p+0,              0x1.01p-53,                  0x1p+0,      -0x1.01p-1, INEXACT)
T(RZ,                  0x1p+0,                -0x1p-54,    0x1.fffffffffffffp-1,         -0x1p-1, INEXACT)
T(RZ,                  0x1p+0,             -0x1.01p-54,    0x1.fffffffffffffp-1,      -0x1.fep-2, INEXACT)
T(RZ,                 -0x1p+0,                -0x1p-53,                 -0x1p+0,          0x1p-1, INEXACT)
T(RZ,                 -0x1p+0,             -0x1.01p-53,                 -0x1p+0,       0x1.01p-1, INEXACT)
T(RZ,                 -0x1p+0,                 0x1p-54,   -0x1.fffffffffffffp-1,          0x1p-1, INEXACT)
T(RZ,                 -0x1p+0,              0x1.01p-54,   -0x1.fffffffffffffp-1,       0x1.fep-2, INEXACT)
};

static void test_round_add(void)
{
	#pragma STDC FENV_ACCESS ON
	double y;
	float d;
	int i;
	struct dd_d *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;

		if (p->r < 0)
			continue;
		fesetround(p->r);
		y = p->x + p->x2;
		d = ulperr(y, p->y, p->dy);
		if (!checkcr(y, p->y, p->r)) {
			printf("%s:%d: %s %a+%a want %a got %a ulperr %.3f = %a + %a\n",
				p->file, p->line, rstr(p->r), p->x, p->x2, p->y, y, d, d-p->dy, p->dy);
			test_status = 1;
		}
	}
}

int main(void)
{
	test_except();
	test_round();
	test_round_add();
	return test_status;
}
