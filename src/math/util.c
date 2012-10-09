#include <stdio.h>
#include <stdint.h>
#include "util.h"

int eulpf(float x)
{
	union { float f; uint32_t i; } u = { x };
	int e = u.i>>23 & 0xff;

	if (!e)
		e++;
	return e - 0x7f - 23;
}

int eulp(double x)
{
	union { double f; uint64_t i; } u = { x };
	int e = u.i>>52 & 0x7ff;

	if (!e)
		e++;
	return e - 0x3ff - 52;
}

int eulpl(long double x)
{
#if LDBL_MANT_DIG == 53
	return eulp(x);
#elif LDBL_MANT_DIG == 64
	union { long double f; struct {uint64_t m; uint16_t e; uint16_t pad;} i; } u = { x };
	int e = u.i.e & 0x7fff;

	if (!e)
		e++;
	return e - 0x3fff - 63;
#else
	// TODO
	return 0;
#endif
}

float ulperrf(float got, float want, float dwant)
{
	if (isnan(got) && isnan(want))
		return 0;
	if (got == want && signbit(got) == signbit(want))
		return dwant;
	if (isinf(got)) {
		got = copysignf(0x1p127, got);
		want *= 0.5;
	}
	return scalbn(got - want, -eulpf(want)) + dwant;
}

float ulperr(double got, double want, float dwant)
{
	if (isnan(got) && isnan(want))
		return 0;
	if (got == want && signbit(got) == signbit(want))
		return dwant;
	if (isinf(got)) {
		got = copysign(0x1p1023, got);
		want *= 0.5;
	}
	return scalbn(got - want, -eulp(want)) + dwant;
}

float ulperrl(long double got, long double want, float dwant)
{
#if LDBL_MANT_DIG == 53
	return ulperr(got, want, dwant);
#elif LDBL_MANT_DIG == 64
	if (isnan(got) && isnan(want))
		return 0;
	if (got == want && signbit(got) == signbit(want))
		return dwant;
	if (isinf(got)) {
		got = copysignl(0x1p16383L, got);
		want *= 0.5;
	}
	return scalbn(got - want, -eulpl(want)) + dwant;
#else
	// TODO
	return inf;
#endif
}

#define length(a) (sizeof(a)/sizeof*(a))
#define flag(x) {x, #x}
static struct {
	int flag;
	char *s;
} eflags[] = {
	flag(INEXACT),
	flag(INVALID),
	flag(DIVBYZERO),
	flag(UNDERFLOW),
	flag(OVERFLOW)
};

char *estr(int f)
{
	static char buf[256];
	char *p = buf;
	int i, all = 0;

	for (i = 0; i < length(eflags); i++)
		if (f & eflags[i].flag) {
			p += sprintf(p, "%s%s", all ? "|" : "", eflags[i].s);
			all |= eflags[i].flag;
		}
	if (all != f) {
		p += sprintf(p, "%s%d", all ? "|" : "", f & ~all);
		all = f;
	}
	p += sprintf(p, "%s", all ? "" : "0");
	return buf;
}

char *rstr(int r)
{
	switch (r) {
	case RN: return "RN";
	case RZ: return "RZ";
	case RU: return "RU";
	case RD: return "RD";
	}
	return "R?";
}
