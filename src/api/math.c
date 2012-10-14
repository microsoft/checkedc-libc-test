#include <math.h>
#define T(t) (t*)0;
#define C(n) switch(n){case n:;}
#define I(n) {int i = n;}
#define D(n) {double d = n;}
static void f()
{
T(float_t)
T(double_t)
I(fpclassify(.0))
I(isfinite(.0))
I(isgreater(.0,.0))
I(isgreaterequal(.0,.0))
I(isinf(.0))
I(isless(.0,.0))
I(islessequal(.0,.0))
I(islessgreater(.0,.0))
I(isnan(.0))
I(isnormal(.0))
I(isunordered(.0,.0))
I(signbit(.0))
#ifdef _XOPEN_SOURCE
I(signgam)
D(M_E)
D(M_LOG2E)
D(M_LOG10E)
D(M_LN2)
D(M_LN10)
D(M_PI)
D(M_PI_2)
D(M_PI_4)
D(M_1_PI)
D(M_2_PI)
D(M_2_SQRTPI)
D(M_SQRT2)
D(M_SQRT1_2)
D(MAXFLOAT)
#endif
D(HUGE_VAL)
D(HUGE_VALF)
D(HUGE_VALL)
D(INFINITY)
D(NAN)
C(FP_INFINITE)
C(FP_NAN)
C(FP_NORMAL)
C(FP_SUBNORMAL)
C(FP_ZERO)
C(FP_ILOGB0)
C(FP_ILOGBNAN)
C(MATH_ERRNO)
C(MATH_ERREXCEPT)
C(math_errhandling)
double(*p_acos)(double) = acos;
float(*p_acosf)(float) = acosf;
double(*p_acosh)(double) = acosh;
float(*p_acoshf)(float) = acoshf;
long double(*p_acoshl)(long double) = acoshl;
long double(*p_acosl)(long double) = acosl;
double(*p_asin)(double) = asin;
float(*p_asinf)(float) = asinf;
double(*p_asinh)(double) = asinh;
float(*p_asinhf)(float) = asinhf;
long double(*p_asinhl)(long double) = asinhl;
long double(*p_asinl)(long double) = asinl;
double(*p_atan)(double) = atan;
double(*p_atan2)(double,double) = atan2;
float(*p_atan2f)(float,float) = atan2f;
long double(*p_atan2l)(long double,long double) = atan2l;
float(*p_atanf)(float) = atanf;
double(*p_atanh)(double) = atanh;
float(*p_atanhf)(float) = atanhf;
long double(*p_atanhl)(long double) = atanhl;
long double(*p_atanl)(long double) = atanl;
double(*p_cbrt)(double) = cbrt;
float(*p_cbrtf)(float) = cbrtf;
long double(*p_cbrtl)(long double) = cbrtl;
double(*p_ceil)(double) = ceil;
float(*p_ceilf)(float) = ceilf;
long double(*p_ceill)(long double) = ceill;
double(*p_copysign)(double,double) = copysign;
float(*p_copysignf)(float,float) = copysignf;
long double(*p_copysignl)(long double,long double) = copysignl;
double(*p_cos)(double) = cos;
float(*p_cosf)(float) = cosf;
double(*p_cosh)(double) = cosh;
float(*p_coshf)(float) = coshf;
long double(*p_coshl)(long double) = coshl;
long double(*p_cosl)(long double) = cosl;
double(*p_erf)(double) = erf;
double(*p_erfc)(double) = erfc;
float(*p_erfcf)(float) = erfcf;
long double(*p_erfcl)(long double) = erfcl;
float(*p_erff)(float) = erff;
long double(*p_erfl)(long double) = erfl;
double(*p_exp)(double) = exp;
double(*p_exp2)(double) = exp2;
float(*p_exp2f)(float) = exp2f;
long double(*p_exp2l)(long double) = exp2l;
float(*p_expf)(float) = expf;
long double(*p_expl)(long double) = expl;
double(*p_expm1)(double) = expm1;
float(*p_expm1f)(float) = expm1f;
long double(*p_expm1l)(long double) = expm1l;
double(*p_fabs)(double) = fabs;
float(*p_fabsf)(float) = fabsf;
long double(*p_fabsl)(long double) = fabsl;
double(*p_fdim)(double,double) = fdim;
float(*p_fdimf)(float,float) = fdimf;
long double(*p_fdiml)(long double,long double) = fdiml;
double(*p_floor)(double) = floor;
float(*p_floorf)(float) = floorf;
long double(*p_floorl)(long double) = floorl;
double(*p_fma)(double,double,double) = fma;
float(*p_fmaf)(float,float,float) = fmaf;
long double(*p_fmal)(long double,long double,long double) = fmal;
double(*p_fmax)(double,double) = fmax;
float(*p_fmaxf)(float,float) = fmaxf;
long double(*p_fmaxl)(long double,long double) = fmaxl;
double(*p_fmin)(double,double) = fmin;
float(*p_fminf)(float,float) = fminf;
long double(*p_fminl)(long double,long double) = fminl;
double(*p_fmod)(double,double) = fmod;
float(*p_fmodf)(float,float) = fmodf;
long double(*p_fmodl)(long double,long double) = fmodl;
double(*p_frexp)(double,int*) = frexp;
float(*p_frexpf)(float,int*) = frexpf;
long double(*p_frexpl)(long double,int*) = frexpl;
double(*p_hypot)(double,double) = hypot;
float(*p_hypotf)(float,float) = hypotf;
long double(*p_hypotl)(long double,long double) = hypotl;
int(*p_ilogb)(double) = ilogb;
int(*p_ilogbf)(float) = ilogbf;
int(*p_ilogbl)(long double) = ilogbl;
#ifdef _XOPEN_SOURCE
double(*p_j0)(double) = j0;
double(*p_j1)(double) = j1;
double(*p_jn)(int,double) = jn;
#endif
double(*p_ldexp)(double,int) = ldexp;
float(*p_ldexpf)(float,int) = ldexpf;
long double(*p_ldexpl)(long double,int) = ldexpl;
double(*p_lgamma)(double) = lgamma;
float(*p_lgammaf)(float) = lgammaf;
long double(*p_lgammal)(long double) = lgammal;
long long(*p_llrint)(double) = llrint;
long long(*p_llrintf)(float) = llrintf;
long long(*p_llrintl)(long double) = llrintl;
long long(*p_llround)(double) = llround;
long long(*p_llroundf)(float) = llroundf;
long long(*p_llroundl)(long double) = llroundl;
double(*p_log)(double) = log;
double(*p_log10)(double) = log10;
float(*p_log10f)(float) = log10f;
long double(*p_log10l)(long double) = log10l;
double(*p_log1p)(double) = log1p;
float(*p_log1pf)(float) = log1pf;
long double(*p_log1pl)(long double) = log1pl;
double(*p_log2)(double) = log2;
float(*p_log2f)(float) = log2f;
long double(*p_log2l)(long double) = log2l;
double(*p_logb)(double) = logb;
float(*p_logbf)(float) = logbf;
long double(*p_logbl)(long double) = logbl;
float(*p_logf)(float) = logf;
long double(*p_logl)(long double) = logl;
long(*p_lrint)(double) = lrint;
long(*p_lrintf)(float) = lrintf;
long(*p_lrintl)(long double) = lrintl;
long(*p_lround)(double) = lround;
long(*p_lroundf)(float) = lroundf;
long(*p_lroundl)(long double) = lroundl;
double(*p_modf)(double,double*) = modf;
float(*p_modff)(float,float*) = modff;
long double(*p_modfl)(long double,long double*) = modfl;
double(*p_nan)(const char*) = nan;
float(*p_nanf)(const char*) = nanf;
long double(*p_nanl)(const char*) = nanl;
double(*p_nearbyint)(double) = nearbyint;
float(*p_nearbyintf)(float) = nearbyintf;
long double(*p_nearbyintl)(long double) = nearbyintl;
double(*p_nextafter)(double,double) = nextafter;
float(*p_nextafterf)(float,float) = nextafterf;
long double(*p_nextafterl)(long double,long double) = nextafterl;
double(*p_nexttoward)(double,long double) = nexttoward;
float(*p_nexttowardf)(float,long double) = nexttowardf;
long double(*p_nexttowardl)(long double,long double) = nexttowardl;
double(*p_pow)(double,double) = pow;
float(*p_powf)(float,float) = powf;
long double(*p_powl)(long double,long double) = powl;
double(*p_remainder)(double,double) = remainder;
float(*p_remainderf)(float,float) = remainderf;
long double(*p_remainderl)(long double,long double) = remainderl;
double(*p_remquo)(double,double,int*) = remquo;
float(*p_remquof)(float,float,int*) = remquof;
long double(*p_remquol)(long double,long double,int*) = remquol;
double(*p_rint)(double) = rint;
float(*p_rintf)(float) = rintf;
long double(*p_rintl)(long double) = rintl;
double(*p_round)(double) = round;
float(*p_roundf)(float) = roundf;
long double(*p_roundl)(long double) = roundl;
double(*p_scalbln)(double,long) = scalbln;
float(*p_scalblnf)(float,long) = scalblnf;
long double(*p_scalblnl)(long double,long) = scalblnl;
double(*p_scalbn)(double,int) = scalbn;
float(*p_scalbnf)(float,int) = scalbnf;
long double(*p_scalbnl)(long double,int) = scalbnl;
double(*p_sin)(double) = sin;
float(*p_sinf)(float) = sinf;
double(*p_sinh)(double) = sinh;
float(*p_sinhf)(float) = sinhf;
long double(*p_sinhl)(long double) = sinhl;
long double(*p_sinl)(long double) = sinl;
double(*p_sqrt)(double) = sqrt;
float(*p_sqrtf)(float) = sqrtf;
long double(*p_sqrtl)(long double) = sqrtl;
double(*p_tan)(double) = tan;
float(*p_tanf)(float) = tanf;
double(*p_tanh)(double) = tanh;
float(*p_tanhf)(float) = tanhf;
long double(*p_tanhl)(long double) = tanhl;
long double(*p_tanl)(long double) = tanl;
double(*p_tgamma)(double) = tgamma;
float(*p_tgammaf)(float) = tgammaf;
long double(*p_tgammal)(long double) = tgammal;
double(*p_trunc)(double) = trunc;
float(*p_truncf)(float) = truncf;
long double(*p_truncl)(long double) = truncl;
#ifdef _XOPEN_SOURCE
double(*p_y0)(double) = y0;
double(*p_y1)(double) = y1;
double(*p_yn)(int,double) = yn;
#endif
}
