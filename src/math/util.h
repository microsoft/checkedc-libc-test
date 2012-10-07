#include <fenv.h>
#include <float.h>
#include <math.h>

#undef RN
#undef RZ
#undef RD
#undef RU
#define RN FE_TONEAREST
#define RZ FE_TOWARDZERO
#define RD FE_DOWNWARD
#define RU FE_UPWARD

#undef INEXACT
#undef INVALID
#undef DIVBYZERO
#undef UNDERFLOW
#undef OVERFLOW
#define INEXACT FE_INEXACT
#define INVALID FE_INVALID
#define DIVBYZERO FE_DIVBYZERO
#define UNDERFLOW FE_UNDERFLOW
#define OVERFLOW FE_OVERFLOW

#undef inf
#undef nan
#define inf INFINITY
#define nan NAN

#define T(...) {__FILE__, __LINE__, __VA_ARGS__},

#define POS char *file; int line;
struct d_d {POS int r; double x; double y; float dy; int e; };
struct f_f {POS int r; float x; float y; float dy; int e; };
struct l_l {POS int r; long double x; long double y; float dy; int e; };
struct ff_f {POS int r; float x; float x2; float y; float dy; int e; };
struct dd_d {POS int r; double x; double x2; double y; float dy; int e; };
struct ll_l {POS int r; long double x; long double x2; long double y; float dy; int e; };

char *estr(int);
char *rstr(int);
int rconv(int *, char *);
int econv(int *, char *);

int eulp(double);
int eulpf(float);
int eulpl(long double);

float ulperr(double got, double want, float dwant);
float ulperrf(float got, float want, float dwant);
float ulperrl(long double got, long double want, float dwant);

void setupfenv(int);
int getexcept(void);

static int checkexcept(int got, int want, int r)
{
	if (r == RN)
		return got == want || got == (want|INEXACT);
	return 1; //(got|INEXACT|UNDERFLOW) == (want|INEXACT|UNDERFLOW);
}

static int checkulp(float d, int r)
{
	if (r == RN)
		return fabsf(d) <= 1.0;
	return 1; //fabsf(d) <= 2.0;
}

