#include <stdio.h>
#include <math.h>
#include "test.h"

static int check(double a, double b)
{
	double d = a - b;
	return fabs(d) <= 0x1p-52*fabs(a);
}

static int checkf(float a, float b)
{
	float d = a - b;
	return fabsf(d) <= 0x1p-23*fabsf(a);
}

static int checkl(long double a, long double b)
{
	long double d = a - b;
	return fabsl(d) <= 0x1p-63L*fabsl(a);
}

#define D(fx, y) do{ \
	double yy = fx; \
	if (!check(yy, y)) \
		error("%s got %a = %.21e want %a = %.21e\n", #fx, yy, yy, y, y); \
}while(0)

#define F(fx, y) do{ \
	float yy = fx; \
	if (!checkf(yy, y)) \
		error("%s got %a = %.21e want %a = %.21e\n", #fx, yy, yy, y, y); \
}while(0)

#define L(fx, y) do{ \
	long double yy = fx; \
	if (!checkl(yy, y)) \
		error("%s got %La = %.21Le want %La = %.21Le\n", #fx, yy, yy, y, y); \
}while(0)

#define I(fx, y) do{ \
	int yy = fx; \
	if (yy != y) \
		error("%s got %d want %d\n", #fx, yy, y); \
}while(0)

#define IL(fx, y) do{ \
	long yy = fx; \
	if (yy != y) \
		error("%s got %ld want %ld\n", #fx, yy, y); \
}while(0)

#define ILL(fx, y) do{ \
	long long yy = fx; \
	if (yy != y) \
		error("%s got %lld want %lld\n", #fx, yy, y); \
}while(0)

void test_math_sanity()
{
	int i;
	double q;
	float qf;
	long double ql;

D(acos(0.7), 0x1.973e83f5d5c9bp-1);
F(acosf(0.7f), 0x1.973e84p-1);
L(acosl(0.7L), 0x1.973e83f5d5c9aaf8p-1L);
D(acosh(1.7), 0x1.1f8c10d010fe6p+0);
F(acoshf(1.7f), 0x1.1f8c12p+0);
L(acoshl(1.7L), 0x1.1f8c10d010fe5d96p+0L);
D(asin(0.7), 0x1.8d00e692afd95p-1);
F(asinf(0.7f), 0x1.8d00e6p-1);
L(asinl(0.7L), 0x1.8d00e692afd95ddap-1L);
D(asinh(0.7), 0x1.4e2a4fe9085ddp-1);
F(asinhf(0.7f), 0x1.4e2a5p-1);
L(asinhl(0.7L), 0x1.4e2a4fe9085dd732p-1L);
D(atan(0.7), 0x1.38b112d7bd4adp-1);
F(atanf(0.7f), 0x1.38b112p-1);
L(atanl(0.7L), 0x1.38b112d7bd4ad786p-1L);
D(atan2(0.7, 1.0), 0x1.38b112d7bd4adp-1);
F(atan2f(0.7f, 1.0f), 0x1.38b112p-1);
L(atan2l(0.7L, 1.0L), 0x1.38b112d7bd4ad786p-1L);
D(atanh(0.7), 0x1.bc0ed0947fbe8p-1);
F(atanhf(0.7f), 0x1.bc0edp-1);
L(atanhl(0.7L), 0x1.bc0ed0947fbe9068p-1L);
D(cbrt(0.7), 0x1.c69b5a72f1a99p-1);
F(cbrtf(0.7f), 0x1.c69b5ap-1);
L(cbrtl(0.7L), 0x1.c69b5a72f1a99902p-1L);
D(ceil(0.7), 0x1p+0);
F(ceilf(0.7f), 0x1p+0);
L(ceill(0.7L), 0x1p+0L);
D(copysign(0.7, -1.0), -0x1.6666666666666p-1);
F(copysignf(0.7f, -1.0f), -0x1.666666p-1);
L(copysignl(0.7L, -1.0L), -0x1.6666666666666666p-1L);
D(cos(0.7), 0x1.87996529f9d93p-1);
F(cosf(0.7f), 0x1.879966p-1);
L(cosl(0.7L), 0x1.87996529f9d92618p-1L);
D(cosh(0.7), 0x1.4152c1862342fp+0);
F(coshf(0.7f), 0x1.4152c2p+0);
L(coshl(0.7L), 0x1.4152c1862342ef8ep+0L);
D(erf(0.7), 0x1.5b08c21171646p-1);
F(erff(0.7f), 0x1.5b08c2p-1);
L(erfl(0.7L), 0x1.5b08c21171646544p-1L);
D(erfc(0.7), 0x1.49ee7bdd1d374p-2);
F(erfcf(0.7f), 0x1.49ee7cp-2);
L(erfcl(0.7L), 0x1.49ee7bdd1d373576p-2L);
D(exp(0.7), 0x1.01c2a61268987p+1);
F(expf(0.7f), 0x1.01c2a6p+1);
L(expl(0.7L), 0x1.01c2a61268986bfep+1L);
D(exp2(0.7), 0x1.9fdf8bcce533dp+0);
F(exp2f(0.7f), 0x1.9fdf8cp+0);
L(exp2l(0.7L), 0x1.9fdf8bcce533d72p+0L);
D(expm1(0.7), 0x1.03854c24d130dp+0);
F(expm1f(0.7f), 0x1.03854cp+0);
L(expm1l(0.7L), 0x1.03854c24d130d7fep+0L);
D(fabs(-0.7), 0x1.6666666666666p-1);
F(fabsf(-0.7f), 0x1.666666p-1);
L(fabsl(-0.7L), 0x1.6666666666666666p-1L);
D(fdim(0.7, 0.5), 0x1.9999999999998p-3);
F(fdimf(0.7f, 0.5f), 0x1.999998p-3);
L(fdiml(0.7L, 0.5L), 0x1.9999999999999998p-3L);
D(floor(0.7), 0x0p+0);
F(floorf(0.7f), 0x0p+0);
L(floorl(0.7L), 0x0p+0L);
D(fma(0.7, 2.0, 0.1), 0x1.8p+0);
F(fmaf(0.7f, 2.0f, 0.1f), 0x1.8p+0);
L(fmal(0.7L, 2.0L, 0.1L), 0x1.8p+0L);
D(fmax(0.7, 0.5), 0x1.6666666666666p-1);
F(fmaxf(0.7f, 0.5), 0x1.666666p-1);
L(fmaxl(0.7L, 0.5), 0x1.6666666666666666p-1L);
D(fmin(0.7, 0.5), 0x1p-1);
F(fminf(0.7f, 0.5f), 0x1p-1);
L(fminl(0.7L, 0.5L), 0x1p-1L);
D(fmod(0.7, 0.5), 0x1.9999999999998p-3);
F(fmodf(0.7f, 0.5f), 0x1.999998p-3);
L(fmodl(0.7L, 0.5L), 0x1.9999999999999998p-3L);
D(frexp(0.7, &i), 0x1.6666666666666p-1);
F(frexpf(0.7f, &i), 0x1.666666p-1);
L(frexpl(0.7L, &i), 0x1.6666666666666666p-1L);
D(hypot(0.7, 1.0), 0x1.387ce204a35d2p+0);
F(hypotf(0.7f, 1.0f), 0x1.387ce2p+0);
L(hypotl(0.7L, 1.0L), 0x1.387ce204a35d1ff6p+0L);
I(ilogb(0.7), -1);
I(ilogbf(0.7f), -1);
I(ilogbl(0.7L), -1);
D(j0(0.7), 0x1.c32cc34b8cc59p-1);
F(j0f(0.7f), 0x1.c32cc4p-1);
D(j1(0.7), 0x1.50e44279c0546p-2);
F(j1f(0.7f), 0x1.50e442p-2);
D(jn(2, 0.7), 0x1.e195286f3b2fbp-5);
F(jnf(2, 0.7f), 0x1.e19528p-5);
D(ldexp(0.7, 3), 0x1.6666666666666p+2);
F(ldexpf(0.7f, 3), 0x1.666666p+2);
L(ldexpl(0.7L, 3), 0x1.6666666666666666p+2L);
D(lgamma(0.7), 0x1.0b20c891cde73p-2);
F(lgammaf(0.7f), 0x1.0b20cap-2);
L(lgammal(0.7L), 0x1.0b20c891cde72846p-2L);
D(lgamma_r(0.7, &i), 0x1.0b20c891cde73p-2);
F(lgammaf_r(0.7f, &i), 0x1.0b20cap-2);
L(lgammal_r(0.7L, &i), 0x1.0b20c891cde72846p-2L);
ILL(llrint(0.7), 1);
ILL(llrintf(0.7f), 1);
ILL(llrintl(0.7l), 1);
ILL(llround(0.7), 1);
ILL(llroundf(0.7f), 1);
ILL(llroundl(0.7L), 1);
D(log(0.7), -0x1.6d3c324e13f5p-2);
F(logf(0.7f), -0x1.6d3c34p-2);
L(logl(0.7L), -0x1.6d3c324e13f4ec54p-2L);
D(log10(0.7), -0x1.3d3d3d21ccf04p-3);
F(log10f(0.7f), -0x1.3d3d3ep-3);
L(log10l(0.7L), -0x1.3d3d3d21ccf035a6p-3L);
D(log1p(0.7), 0x1.0fae81914a991p-1);
F(log1pf(0.7f), 0x1.0fae82p-1);
L(log1pl(0.7L), 0x1.0fae81914a991308p-1L);
D(log2(0.7), -0x1.0776228967d13p-1);
F(log2f(0.7f), -0x1.077624p-1);
L(log2l(0.7L), -0x1.0776228967d1218cp-1L);
D(logb(0.7), -0x1p+0);
F(logbf(0.7f), -0x1p+0);
L(logbl(0.7L), -0x1p+0L);
IL(lrint(0.7), 1);
IL(lrintf(0.7f), 1);
IL(lrintl(0.7l), 1);
IL(lround(0.7), 1);
IL(lroundf(0.7f), 1);
IL(lroundl(0.7L), 1);
D(modf(0.7, &q), 0x1.6666666666666p-1);
F(modff(0.7f, &qf), 0x1.666666p-1);
L(modfl(0.7L, &ql), 0x1.6666666666666666p-1L);
D(nearbyint(0.7), 0x1p+0);
F(nearbyintf(0.7f), 0x1p+0);
L(nearbyintl(0.7L), 0x1p+0L);
D(nextafter(0.7, 1.0), 0x1.6666666666667p-1);
F(nextafterf(0.7f, 1.0f), 0x1.666668p-1);
L(nextafterl(0.7L, 1.0L), 0x1.6666666666666667p-1L);
D(nexttoward(0.7, 1.0L), 0x1.6666666666667p-1);
F(nexttowardf(0.7f, 1.0L), 0x1.666668p-1);
L(nexttowardl(0.7L, 1.0L), 0x1.6666666666666667p-1L);
D(pow(0.7, 1.5), 0x1.2bdbe460916ep-1);
F(powf(0.7f, 1.5f), 0x1.2bdbe4p-1);
L(powl(0.7L, 1.5L), 0x1.2bdbe460916e0b5p-1L);
D(remainder(0.7, 0.5), 0x1.9999999999998p-3);
F(remainderf(0.7f, 0.5f), 0x1.999998p-3);
L(remainderl(0.7L, 0.5L), 0x1.9999999999999998p-3L);
D(remquo(0.7, 0.5, &i), 0x1.9999999999998p-3);
F(remquof(0.7f, 0.5f, &i), 0x1.999998p-3);
L(remquol(0.7L, 0.5L, &i), 0x1.9999999999999998p-3L);
D(rint(0.7), 0x1p+0);
F(rintf(0.7f), 0x1p+0);
L(rintl(0.7L), 0x1p+0L);
D(round(0.7), 0x1p+0);
F(roundf(0.7f), 0x1p+0);
L(roundl(0.7L), 0x1p+0L);
D(scalb(0.7, 3), 0x1.6666666666666p+2);
F(scalbf(0.7f, 3), 0x1.666666p+2);
D(scalbln(0.7, 3), 0x1.6666666666666p+2);
F(scalblnf(0.7f, 3), 0x1.666666p+2);
L(scalblnl(0.7L, 3), 0x1.6666666666666666p+2L);
D(scalbn(0.7, 3), 0x1.6666666666666p+2);
F(scalbnf(0.7f, 3), 0x1.666666p+2);
L(scalbnl(0.7L, 3), 0x1.6666666666666666p+2L);
D(sin(0.7), 0x1.49d6e694619b8p-1);
F(sinf(0.7f), 0x1.49d6e6p-1);
L(sinl(0.7L), 0x1.49d6e694619b854ep-1L);
D(sinh(0.7), 0x1.8465153d5bdbdp-1);
F(sinhf(0.7f), 0x1.846514p-1);
L(sinhl(0.7L), 0x1.8465153d5bdbd0dep-1L);
D(sqrt(0.7), 0x1.ac5eb3f7ab2f8p-1);
F(sqrtf(0.7f), 0x1.ac5eb4p-1);
L(sqrtl(0.7L), 0x1.ac5eb3f7ab2f7de2p-1L);
D(tan(0.7), 0x1.af406c2fc78aep-1);
F(tanf(0.7f), 0x1.af406cp-1);
L(tanl(0.7L), 0x1.af406c2fc78ae54cp-1L);
D(tanh(0.7), 0x1.356fb17af2e91p-1);
F(tanhf(0.7f), 0x1.356fb2p-1);
L(tanhl(0.7L), 0x1.356fb17af2e9100ap-1L);
D(tgamma(0.7), 0x1.4c4d5ab21ea23p+0);
F(tgammaf(0.7f), 0x1.4c4d5cp+0);
L(tgammal(0.7L), 0x1.4c4d5ab21ea22798p+0L);
D(trunc(0.7), 0x0p+0);
F(truncf(0.7f), 0x0p+0);
L(truncl(0.7L), 0x0p+0L);
D(y0(0.7), -0x1.867b559ffc715p-3);
F(y0f(0.7f), -0x1.867b58p-3);
D(y1(0.7), -0x1.1a6e956728d35p+0);
F(y1f(0.7f), -0x1.1a6e96p+0);
D(yn(2, 0.7), -0x1.7b11b25df166ep+1);
F(ynf(2, 0.7f), -0x1.7b11b4p+1);
}
