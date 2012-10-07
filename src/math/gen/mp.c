#include <stdio.h>

#include <stdint.h>
#include <mpfr.h>
#include "gen.h"

static int rmap(int r)
{
	switch (r) {
	case RN: return MPFR_RNDN;
	case RZ: return MPFR_RNDZ;
	case RD: return MPFR_RNDD;
	case RU: return MPFR_RNDU;
	}
	return -1;
}

void debug(mpfr_t x)
{
	mpfr_out_str(stdout, 10, 0, x, MPFR_RNDN);
	printf("\n");
}

void mpsetup()
{
	mpfr_set_emin(-1073);
	mpfr_set_emax(1024);
}
void mpsetupf()
{
	mpfr_set_emin(-148);
	mpfr_set_emax(128);
}
#if LDBL_MANT_DIG == 64
void mpsetupl()
{
	mpfr_set_emin(-16444);
	mpfr_set_emax(16384);
}
#endif

/*
round x into y considering x is already rounded (t = up or down)

only cases where adjustment is done:
	x=...|1...0, t=up    -> x=nextbelow(x)
	x=...|1...0, t=down  -> x=nextabove(x)
where | is the rounding point, ... is 0 or 1 bit patterns
*/

// TODO: adjust(y, 0, 2, RN); when prec is 24 (0 vs 0x1p-149f), special case x=0
static int adjust_round(mpfr_t y, mpfr_t x, int t, int r)
{
	mp_limb_t *p, *q;
	unsigned xp, yp;
	int t2;

	xp = mpfr_get_prec(x);
	yp = mpfr_get_prec(y);
	if (yp >= xp || r != MPFR_RNDN || t == 0 || !mpfr_number_p(x) || mpfr_zero_p(x)) {
		t2 = mpfr_set(y, x, r);
		return t2 ? t2 : t;
	}
	p = x->_mpfr_d;
	yp++;
	q = p + (xp + mp_bits_per_limb - 1)/mp_bits_per_limb - (yp + mp_bits_per_limb - 1)/mp_bits_per_limb;
	if ((*p & 1 << -xp%mp_bits_per_limb) || !(*q & 1 << -yp%mp_bits_per_limb)) {
		t2 = mpfr_set(y, x, r);
		return t2 ? t2 : t;
	}
	if (t > 0)
		mpfr_nextbelow(x);
	else
		mpfr_nextabove(x);
	return mpfr_set(y, x, r);
}

static int adjust(mpfr_t mr, mpfr_t my, int t, int r)
{
//	double d, dn, dp;
//printf("adj %d\n", t);
//debug(my);
	t = adjust_round(mr, my, t, r);
//printf("rnd %d\n", t);
//debug(mr);
	t = mpfr_subnormalize(mr, t, r);
//printf("sub %d\n", t);
//debug(mr);
//	d = mpfr_get_d(mr, r);
//	dn = nextafter(d, INFINITY);
//	dp = nextafter(d, -INFINITY);
//printf("c\n %.21e %a\n %.21e %a\n %.21e %a\n",d,d,dn,dn,dp,dp);
//	dn = nextafterf(d, INFINITY);
//	dp = nextafterf(d, -INFINITY);
//printf("cf\n %.21e %a\n %.21e %a\n %.21e %a\n",d,d,dn,dn,dp,dp);
	return t;
}

// TODO
//static int eflags(mpfr_t mr, mpfr_t my, int t)
static int eflags(int naninput)
{
	int i = 0;

	if (mpfr_inexflag_p())
		i |= FE_INEXACT;
//	if (mpfr_underflow_p() && (t || mpfr_cmp(mr, my) != 0))
	if (mpfr_underflow_p() && i)
		i |= FE_UNDERFLOW;
	if (mpfr_overflow_p())
		i |= FE_OVERFLOW;
	if (mpfr_divby0_p())
		i |= FE_DIVBYZERO;
	if (!naninput && (mpfr_nanflag_p() || mpfr_erangeflag_p()))
		i |= FE_INVALID;
	return i;
}

static void genf(struct t *p, mpfr_t my, int t, int r)
{
	MPFR_DECL_INIT(mr, 24);
	int i;

	t = adjust(mr, my, t, r);
	p->y = mpfr_get_flt(mr, r);
	p->e = eflags(isnan(p->x) || isnan(p->x2));
	i = eulpf(p->y);
	if (!isfinite(p->y)) {
		p->dy = 0;
	} else if (i < 0) {
		mpfr_div_2si(mr, mr, i, MPFR_RNDN);
		mpfr_div_2si(my, my, i, MPFR_RNDN);
		mpfr_sub(my, mr, my, MPFR_RNDN);
		p->dy = mpfr_get_flt(my, r);
	} else {
		mpfr_sub(my, mr, my, MPFR_RNDN);
		mpfr_div_2si(my, my, i, MPFR_RNDN);
		p->dy = mpfr_get_flt(my, r);
	}
}

static int mpf1(struct t *p, int (*fmp)(mpfr_t, const mpfr_t, mpfr_rnd_t))
{
	int tn;
	int r = rmap(p->r);
	MPFR_DECL_INIT(mx, 24);
	MPFR_DECL_INIT(my, 128);

	mpsetupf();
	mpfr_clear_flags();
	mpfr_set_flt(mx, p->x, MPFR_RNDN);
	tn = fmp(my, mx, r);
	p->x2 = 0;
	genf(p, my, tn, r);
	if ((p->e & INEXACT) && nextafterf(p->y, 0) == 0) {
		mpfr_set_emin(-(1<<20));
		tn = fmp(my, mx, r);
		mpfr_mul_2si(my, my, 149, MPFR_RNDN);
		p->dy = scalbnl(p->y, 149) - mpfr_get_ld(my, r);
		mpfr_set_emin(-148);
	}
	return 0;
}

static int mpf2(struct t *p, int (*fmp)(mpfr_t, const mpfr_t, const mpfr_t, mpfr_rnd_t))
{
	int tn;
	int r = rmap(p->r);
	MPFR_DECL_INIT(mx, 24);
	MPFR_DECL_INIT(mx2, 24);
	MPFR_DECL_INIT(my, 128);

	mpsetupf();
	mpfr_clear_flags();
	mpfr_set_flt(mx, p->x, MPFR_RNDN);
	mpfr_set_flt(mx2, p->x2, MPFR_RNDN);
	tn = fmp(my, mx, mx2, r);
	genf(p, my, tn, r);
	if ((p->e & INEXACT) && nextafterf(p->y, 0) == 0) {
		mpfr_set_emin(-(1<<20));
		tn = fmp(my, mx, mx2, r);
		mpfr_mul_2si(my, my, 149, MPFR_RNDN);
		p->dy = scalbnl(p->y, 149) - mpfr_get_ld(my, r);
		mpfr_set_emin(-148);
	}
	return 0;
}

static void gend(struct t *p, mpfr_t my, int t, int r)
{
	MPFR_DECL_INIT(mr, 53);
	int i;

	t = adjust(mr, my, t, r);
	p->y = mpfr_get_d(mr, r);
	p->e = eflags(isnan(p->x) || isnan(p->x2));
	i = eulp(p->y);
	if (!isfinite(p->y)) {
		p->dy = 0;
	} else if (i < 0) {
		mpfr_div_2si(mr, mr, i, MPFR_RNDN);
		mpfr_div_2si(my, my, i, MPFR_RNDN);
		mpfr_sub(my, mr, my, MPFR_RNDN);
		p->dy = mpfr_get_flt(my, r);
	} else {
		mpfr_sub(my, mr, my, MPFR_RNDN);
		mpfr_div_2si(my, my, i, MPFR_RNDN);
		p->dy = mpfr_get_flt(my, r);
	}
}

static int mpd1(struct t *p, int (*fmp)(mpfr_t, const mpfr_t, mpfr_rnd_t))
{
	int tn;
	int r = rmap(p->r);
	MPFR_DECL_INIT(mx, 53);
	MPFR_DECL_INIT(my, 128);

	mpsetup();
	mpfr_clear_flags();
	mpfr_set_d(mx, p->x, MPFR_RNDN);
	tn = fmp(my, mx, r);
//printf("underflow: %d\n", mpfr_underflow_p());
	p->x2 = 0;
	gend(p, my, tn, r);
//printf("dy: %a  %.3f\n", p->dy, p->dy);
	if ((p->e & INEXACT) && nextafter(p->y, 0) == 0) {
		mpfr_set_emin(-(1<<20));
		tn = fmp(my, mx, r);
		mpfr_mul_2si(my, my, 1074, MPFR_RNDN);
//debug(my);
		p->dy = scalbnl(p->y, 1074) - mpfr_get_ld(my, r);
//printf("dy: %a  %.3f\n", p->dy, p->dy);
		mpfr_set_emin(-1073);
	}
	return 0;
}

static int mpd2(struct t *p, int (*fmp)(mpfr_t, const mpfr_t, const mpfr_t, mpfr_rnd_t))
{
	int tn;
	int r = rmap(p->r);
	MPFR_DECL_INIT(mx, 53);
	MPFR_DECL_INIT(mx2, 53);
	MPFR_DECL_INIT(my, 128);

	mpsetup();
	mpfr_clear_flags();
	mpfr_set_d(mx, p->x, MPFR_RNDN);
	mpfr_set_d(mx2, p->x2, MPFR_RNDN);
	tn = fmp(my, mx, mx2, r);
	gend(p, my, tn, r);
	if ((p->e & INEXACT) && nextafter(p->y, 0) == 0) {
		mpfr_set_emin(-(1<<20));
		tn = fmp(my, mx, mx2, r);
		mpfr_mul_2si(my, my, 1074, MPFR_RNDN);
		p->dy = scalbnl(p->y, 1074) - mpfr_get_ld(my, r);
		mpfr_set_emin(-1073);
	}
	return 0;
}

#if LDBL_MANT_DIG == 64
static void genl(struct t *p, mpfr_t my, int t, int r)
{
	MPFR_DECL_INIT(mr, 64);
	int i;

	t = adjust(mr, my, t, r);
	p->y = mpfr_get_ld(mr, r);
	p->e = eflags(isnan(p->x) || isnan(p->x2));
	i = eulpl(p->y);
	if (!isfinite(p->y)) {
		p->dy = 0;
	} else if (i < 0) {
		mpfr_div_2si(mr, mr, i, MPFR_RNDN);
		mpfr_div_2si(my, my, i, MPFR_RNDN);
		mpfr_sub(my, mr, my, MPFR_RNDN);
		p->dy = mpfr_get_flt(my, r);
	} else {
		mpfr_sub(my, mr, my, MPFR_RNDN);
		mpfr_div_2si(my, my, i, MPFR_RNDN);
		p->dy = mpfr_get_flt(my, r);
	}
}
#endif

static int mpl1(struct t *p, int (*fmp)(mpfr_t, const mpfr_t, mpfr_rnd_t))
{
#if LDBL_MANT_DIG == 53
	return mpd1(p, fmp);
#elif LDBL_MANT_DIG == 64
	int tn;
	int r = rmap(p->r);
	MPFR_DECL_INIT(mx, 64);
	MPFR_DECL_INIT(my, 128);

	mpsetupl();
	mpfr_clear_flags();
	mpfr_set_ld(mx, p->x, MPFR_RNDN);
	tn = fmp(my, mx, r);
	p->x2 = 0;
	genl(p, my, tn, r);
	if ((p->e & INEXACT) && nextafterl(p->y, 0) == 0) {
		mpfr_set_emin(-(1<<20));
		tn = fmp(my, mx, r);
		mpfr_mul_2si(my, my, 16445, MPFR_RNDN);
		p->dy = scalbnl(p->y, 16445) - mpfr_get_ld(my, r);
		mpfr_set_emin(-16444);
	}
	return 0;
#else
	return -1;
#endif
}

static int mpl2(struct t *p, int (*fmp)(mpfr_t, const mpfr_t, const mpfr_t, mpfr_rnd_t))
{
#if LDBL_MANT_DIG == 53
	return mpd2(p, fmp);
#elif LDBL_MANT_DIG == 64
	int tn;
	int r = rmap(p->r);
	MPFR_DECL_INIT(mx, 64);
	MPFR_DECL_INIT(mx2, 64);
	MPFR_DECL_INIT(my, 128);

	mpsetupl();
	mpfr_clear_flags();
	mpfr_set_ld(mx, p->x, MPFR_RNDN);
	mpfr_set_ld(mx2, p->x2, MPFR_RNDN);
	tn = fmp(my, mx, mx2, r);
	genl(p, my, tn, r);
	if ((p->e & INEXACT) && nextafterl(p->y, 0) == 0) {
		mpfr_set_emin(-(1<<20));
		tn = fmp(my, mx, mx2, r);
		mpfr_mul_2si(my, my, 16445, MPFR_RNDN);
		p->dy = scalbnl(p->y, 16445) - mpfr_get_ld(my, r);
		mpfr_set_emin(-16444);
	}
	return 0;
#else
	return -1;
#endif
}

// TODO
static int mplgamma_sign;
static int wrap_lgamma(mpfr_t my, const mpfr_t mx, mpfr_rnd_t r)
{
	return mpfr_lgamma(my, &mplgamma_sign, mx, r);
}
static int wrap_ceil(mpfr_t my, const mpfr_t mx, mpfr_rnd_t r)
{
	return mpfr_ceil(my, mx);
}
static int wrap_floor(mpfr_t my, const mpfr_t mx, mpfr_rnd_t r)
{
	return mpfr_floor(my, mx);
}
static int wrap_round(mpfr_t my, const mpfr_t mx, mpfr_rnd_t r)
{
	return mpfr_round(my, mx);
}
static int wrap_trunc(mpfr_t my, const mpfr_t mx, mpfr_rnd_t r)
{
	return mpfr_trunc(my, mx);
}
static int wrap_nearbyint(mpfr_t my, const mpfr_t mx, mpfr_rnd_t r)
{
	int i = mpfr_rint(my, mx, r);
	mpfr_clear_inexflag();
	return i;
}
static int wrap_pow10(mpfr_t my, const mpfr_t mx, mpfr_rnd_t r)
{
	return mpfr_ui_pow(my, 10, mx, r);
}

int mpacos(struct t *t) { return mpd1(t, mpfr_acos); }
int mpacosf(struct t *t) { return mpf1(t, mpfr_acos); }
int mpacosl(struct t *t) { return mpl1(t, mpfr_acos); }
int mpacosh(struct t *t) { return mpd1(t, mpfr_acosh); }
int mpacoshf(struct t *t) { return mpf1(t, mpfr_acosh); }
int mpacoshl(struct t *t) { return mpl1(t, mpfr_acosh); }
int mpasin(struct t *t) { return mpd1(t, mpfr_asin); }
int mpasinf(struct t *t) { return mpf1(t, mpfr_asin); }
int mpasinl(struct t *t) { return mpl1(t, mpfr_asin); }
int mpasinh(struct t *t) { return mpd1(t, mpfr_asinh); }
int mpasinhf(struct t *t) { return mpf1(t, mpfr_asinh); }
int mpasinhl(struct t *t) { return mpl1(t, mpfr_asinh); }
int mpatan(struct t *t) { return mpd1(t, mpfr_atan); }
int mpatanf(struct t *t) { return mpf1(t, mpfr_atan); }
int mpatanl(struct t *t) { return mpl1(t, mpfr_atan); }
int mpatan2(struct t *t) { return mpd2(t, mpfr_atan2); }
int mpatan2f(struct t *t) { return mpf2(t, mpfr_atan2); }
int mpatan2l(struct t *t) { return mpl2(t, mpfr_atan2); }
int mpatanh(struct t *t) { return mpd1(t, mpfr_atanh); }
int mpatanhf(struct t *t) { return mpf1(t, mpfr_atanh); }
int mpatanhl(struct t *t) { return mpl1(t, mpfr_atanh); }
int mpcbrt(struct t *t) { return mpd1(t, mpfr_cbrt); }
int mpcbrtf(struct t *t) { return mpf1(t, mpfr_cbrt); }
int mpcbrtl(struct t *t) { return mpl1(t, mpfr_cbrt); }
int mpceil(struct t *t) { return mpd1(t, wrap_ceil); }
int mpceilf(struct t *t) { return mpf1(t, wrap_ceil); }
int mpceill(struct t *t) { return mpl1(t, wrap_ceil); }
int mpcopysign(struct t *t) { return mpd2(t, mpfr_copysign); }
int mpcopysignf(struct t *t) { return mpf2(t, mpfr_copysign); }
int mpcopysignl(struct t *t) { return mpl2(t, mpfr_copysign); }
int mpcos(struct t *t) { return mpd1(t, mpfr_cos); }
int mpcosf(struct t *t) { return mpf1(t, mpfr_cos); }
int mpcosl(struct t *t) { return mpl1(t, mpfr_cos); }
int mpcosh(struct t *t) { return mpd1(t, mpfr_cosh); }
int mpcoshf(struct t *t) { return mpf1(t, mpfr_cosh); }
int mpcoshl(struct t *t) { return mpl1(t, mpfr_cosh); }
int mperf(struct t *t) { return mpd1(t, mpfr_erf); }
int mperff(struct t *t) { return mpf1(t, mpfr_erf); }
int mperfl(struct t *t) { return mpl1(t, mpfr_erf); }
int mperfc(struct t *t) { return mpd1(t, mpfr_erfc); }
int mperfcf(struct t *t) { return mpf1(t, mpfr_erfc); }
int mperfcl(struct t *t) { return mpl1(t, mpfr_erfc); }
int mpexp(struct t *t) { return mpd1(t, mpfr_exp); }
int mpexpf(struct t *t) { return mpf1(t, mpfr_exp); }
int mpexpl(struct t *t) { return mpl1(t, mpfr_exp); }
int mpexp2(struct t *t) { return mpd1(t, mpfr_exp2); }
int mpexp2f(struct t *t) { return mpf1(t, mpfr_exp2); }
int mpexp2l(struct t *t) { return mpl1(t, mpfr_exp2); }
int mpexpm1(struct t *t) { return mpd1(t, mpfr_expm1); }
int mpexpm1f(struct t *t) { return mpf1(t, mpfr_expm1); }
int mpexpm1l(struct t *t) { return mpl1(t, mpfr_expm1); }
int mpfabs(struct t *t) { return mpd1(t, mpfr_abs); }
int mpfabsf(struct t *t) { return mpf1(t, mpfr_abs); }
int mpfabsl(struct t *t) { return mpl1(t, mpfr_abs); }
int mpfdim(struct t *t) { return mpd2(t, mpfr_dim); }
int mpfdimf(struct t *t) { return mpf2(t, mpfr_dim); }
int mpfdiml(struct t *t) { return mpl2(t, mpfr_dim); }
int mpfloor(struct t *t) { return mpd1(t, wrap_floor); }
int mpfloorf(struct t *t) { return mpf1(t, wrap_floor); }
int mpfloorl(struct t *t) { return mpl1(t, wrap_floor); }
int mpfmax(struct t *t) { return mpd2(t, mpfr_max); }
int mpfmaxf(struct t *t) { return mpf2(t, mpfr_max); }
int mpfmaxl(struct t *t) { return mpl2(t, mpfr_max); }
int mpfmin(struct t *t) { return mpd2(t, mpfr_min); }
int mpfminf(struct t *t) { return mpf2(t, mpfr_min); }
int mpfminl(struct t *t) { return mpl2(t, mpfr_min); }
int mpfmod(struct t *t) { return mpd2(t, mpfr_fmod); }
int mpfmodf(struct t *t) { return mpf2(t, mpfr_fmod); }
int mpfmodl(struct t *t) { return mpl2(t, mpfr_fmod); }
int mphypot(struct t *t) { return mpd2(t, mpfr_hypot); }
int mphypotf(struct t *t) { return mpf2(t, mpfr_hypot); }
int mphypotl(struct t *t) { return mpl2(t, mpfr_hypot); }
int mplgamma(struct t *t) { return mpd1(t, wrap_lgamma) || (t->i = mplgamma_sign, 0); }
int mplgammaf(struct t *t) { return mpf1(t, wrap_lgamma) || (t->i = mplgamma_sign, 0); }
int mplgammal(struct t *t) { return mpl1(t, wrap_lgamma) || (t->i = mplgamma_sign, 0); }
int mplog(struct t *t) { return mpd1(t, mpfr_log); }
int mplogf(struct t *t) { return mpf1(t, mpfr_log); }
int mplogl(struct t *t) { return mpl1(t, mpfr_log); }
int mplog10(struct t *t) { return mpd1(t, mpfr_log10); }
int mplog10f(struct t *t) { return mpf1(t, mpfr_log10); }
int mplog10l(struct t *t) { return mpl1(t, mpfr_log10); }
int mplog1p(struct t *t) { return mpd1(t, mpfr_log1p); }
int mplog1pf(struct t *t) { return mpf1(t, mpfr_log1p); }
int mplog1pl(struct t *t) { return mpl1(t, mpfr_log1p); }
int mplog2(struct t *t) { return mpd1(t, mpfr_log2); }
int mplog2f(struct t *t) { return mpf1(t, mpfr_log2); }
int mplog2l(struct t *t) { return mpl1(t, mpfr_log2); }
int mplogb(struct t *t)
{
	MPFR_DECL_INIT(mx, 53);

	mpfr_set_d(mx, t->x, MPFR_RNDN);
	t->y = mpfr_get_exp(mx) + 1;
	t->dy = 0;
	t->e = 0;
	return 0;
}
int mplogbf(struct t *t)
{
	MPFR_DECL_INIT(mx, 24);

	mpfr_set_flt(mx, t->x, MPFR_RNDN);
	t->y = mpfr_get_exp(mx) + 1;
	t->dy = 0;
	t->e = 0;
	return 0;
}
int mplogbl(struct t *t)
{
	MPFR_DECL_INIT(mx, 64);

	mpfr_set_ld(mx, t->x, MPFR_RNDN);
	t->y = mpfr_get_exp(mx) + 1;
	t->dy = 0;
	t->e = 0;
	return 0;
}
int mpnearbyint(struct t *t) { return mpd1(t, wrap_nearbyint); }
int mpnearbyintf(struct t *t) { return mpf1(t, wrap_nearbyint); }
int mpnearbyintl(struct t *t) { return mpl1(t, wrap_nearbyint); }
int mpnextafter(struct t *t) { return -1; }
int mpnextafterf(struct t *t) { return -1; }
int mpnextafterl(struct t *t) { return -1; }
int mpnexttowardl(struct t *t) { return -1; }
int mppow(struct t *t) { return mpd2(t, mpfr_pow); }
int mppowf(struct t *t) { return mpf2(t, mpfr_pow); }
int mppowl(struct t *t) { return mpl2(t, mpfr_pow); }
int mpremainder(struct t *t) { return mpd2(t, mpfr_remainder); }
int mpremainderf(struct t *t) { return mpf2(t, mpfr_remainder); }
int mpremainderl(struct t *t) { return mpl2(t, mpfr_remainder); }
int mprint(struct t *t) { return mpd1(t, mpfr_rint); }
int mprintf(struct t *t) { return mpf1(t, mpfr_rint); }
int mprintl(struct t *t) { return mpl1(t, mpfr_rint); }
int mpround(struct t *t) { return mpd1(t, wrap_round); }
int mproundf(struct t *t) { return mpf1(t, wrap_round); }
int mproundl(struct t *t) { return mpl1(t, wrap_round); }
int mpsin(struct t *t) { return mpd1(t, mpfr_sin); }
int mpsinf(struct t *t) { return mpf1(t, mpfr_sin); }
int mpsinl(struct t *t) { return mpl1(t, mpfr_sin); }
int mpsinh(struct t *t) { return mpd1(t, mpfr_sinh); }
int mpsinhf(struct t *t) { return mpf1(t, mpfr_sinh); }
int mpsinhl(struct t *t) { return mpl1(t, mpfr_sinh); }
int mpsqrt(struct t *t) { return mpd1(t, mpfr_sqrt); }
int mpsqrtf(struct t *t) { return mpf1(t, mpfr_sqrt); }
int mpsqrtl(struct t *t) { return mpl1(t, mpfr_sqrt); }
int mptan(struct t *t) { return mpd1(t, mpfr_tan); }
int mptanf(struct t *t) { return mpf1(t, mpfr_tan); }
int mptanl(struct t *t) { return mpl1(t, mpfr_tan); }
int mptanh(struct t *t) { return mpd1(t, mpfr_tanh); }
int mptanhf(struct t *t) { return mpf1(t, mpfr_tanh); }
int mptanhl(struct t *t) { return mpl1(t, mpfr_tanh); }
int mptgamma(struct t *t) { return mpd1(t, mpfr_gamma); }
int mptgammaf(struct t *t) { return mpf1(t, mpfr_gamma); }
int mptgammal(struct t *t) { return mpl1(t, mpfr_gamma); }
int mptrunc(struct t *t) { return mpd1(t, wrap_trunc); }
int mptruncf(struct t *t) { return mpf1(t, wrap_trunc); }
int mptruncl(struct t *t) { return mpl1(t, wrap_trunc); }
int mpj0(struct t *t) { return mpd1(t, mpfr_j0); }
int mpj1(struct t *t) { return mpd1(t, mpfr_j1); }
int mpy0(struct t *t) { return mpd1(t, mpfr_y0); }
int mpy1(struct t *t) { return mpd1(t, mpfr_y1); }
int mpscalb(struct t *t) { return -1; }
int mpscalbf(struct t *t) { return -1; }
int mpj0f(struct t *t) { return mpf1(t, mpfr_j0); }
int mpj0l(struct t *t) { return mpl1(t, mpfr_j0); }
int mpj1f(struct t *t) { return mpf1(t, mpfr_j1); }
int mpj1l(struct t *t) { return mpl1(t, mpfr_j1); }
int mpy0f(struct t *t) { return mpf1(t, mpfr_y0); }
int mpy0l(struct t *t) { return mpl1(t, mpfr_y0); }
int mpy1f(struct t *t) { return mpf1(t, mpfr_y1); }
int mpy1l(struct t *t) { return mpl1(t, mpfr_y1); }
int mpexp10(struct t *t) { return mpd1(t, wrap_pow10); }
int mpexp10f(struct t *t) { return mpf1(t, wrap_pow10); }
int mpexp10l(struct t *t) { return mpl1(t, wrap_pow10); }
int mppow10(struct t *t) { return mpd1(t, wrap_pow10); }
int mppow10f(struct t *t) { return mpf1(t, wrap_pow10); }
int mppow10l(struct t *t) { return mpl1(t, wrap_pow10); }

int mpfrexp(struct t *t)
{
	mpfr_exp_t e;
	int k;
	MPFR_DECL_INIT(mx, 53);

	t->dy = 0;
	t->y = 0;
	mpsetup();
	mpfr_clear_flags();
	mpfr_set_d(mx, t->x, MPFR_RNDN);
	k = mpfr_frexp(&e, mx, mx, t->r);
	mpfr_subnormalize(mx, k, t->r);
	t->y = mpfr_get_d(mx, MPFR_RNDN);
	t->i = e;
	t->e = eflags(isnan(t->x));
	return 0;
}

int mpfrexpf(struct t *t)
{
	mpfr_exp_t e;
	int k;
	MPFR_DECL_INIT(mx, 24);

	t->dy = 0;
	t->y = 0;
	mpsetup();
	mpfr_clear_flags();
	mpfr_set_flt(mx, t->x, MPFR_RNDN);
	k = mpfr_frexp(&e, mx, mx, t->r);
	mpfr_subnormalize(mx, k, t->r);
	t->y = mpfr_get_flt(mx, MPFR_RNDN);
	t->i = e;
	t->e = eflags(isnan(t->x));
	return 0;
}

int mpfrexpl(struct t *t)
{
	mpfr_exp_t e;
	int k;
	MPFR_DECL_INIT(mx, 64);

	t->dy = 0;
	t->y = 0;
	mpsetup();
	mpfr_clear_flags();
	mpfr_set_ld(mx, t->x, MPFR_RNDN);
	k = mpfr_frexp(&e, mx, mx, t->r);
	mpfr_subnormalize(mx, k, t->r);
	t->y = mpfr_get_ld(mx, MPFR_RNDN);
	t->i = e;
	t->e = eflags(isnan(t->x));
	return 0;
}

int mpldexp(struct t *t)
{
	int k;
	MPFR_DECL_INIT(mx, 53);

	t->dy = 0;
	t->y = 0;
	mpsetup();
	mpfr_clear_flags();
	mpfr_set_d(mx, t->x, MPFR_RNDN);
	k = mpfr_mul_2si(mx, mx, t->i, t->r);
	mpfr_subnormalize(mx, k, t->r);
	t->y = mpfr_get_d(mx, MPFR_RNDN);
	t->e = eflags(isnan(t->x));
	return 0;
}

int mpldexpf(struct t *t)
{
	int k;
	MPFR_DECL_INIT(mx, 24);

	t->dy = 0;
	t->y = 0;
	mpsetup();
	mpfr_clear_flags();
	mpfr_set_flt(mx, t->x, MPFR_RNDN);
	k = mpfr_mul_2si(mx, mx, t->i, t->r);
	mpfr_subnormalize(mx, k, t->r);
	t->y = mpfr_get_flt(mx, MPFR_RNDN);
	t->e = eflags(isnan(t->x));
	return 0;
}

int mpldexpl(struct t *t)
{
	int k;
	MPFR_DECL_INIT(mx, 64);

	t->dy = 0;
	t->y = 0;
	mpsetup();
	mpfr_clear_flags();
	mpfr_set_ld(mx, t->x, MPFR_RNDN);
	k = mpfr_mul_2si(mx, mx, t->i, t->r);
	mpfr_subnormalize(mx, k, t->r);
	t->y = mpfr_get_ld(mx, MPFR_RNDN);
	t->e = eflags(isnan(t->x));
	return 0;
}

int mpscalbn(struct t *t) { return mpldexp(t); }
int mpscalbnf(struct t *t) { return mpldexpf(t); }
int mpscalbnl(struct t *t) { return mpldexpl(t); }
int mpscalbln(struct t *t) { return mpldexp(t); }
int mpscalblnf(struct t *t) { return mpldexpf(t); }
int mpscalblnl(struct t *t) { return mpldexpl(t); }

int mplgamma_r(struct t *t) { return mplgamma(t); }
int mplgammaf_r(struct t *t) { return mplgammaf(t); }
int mplgammal_r(struct t *t) { return mplgammal(t); }
