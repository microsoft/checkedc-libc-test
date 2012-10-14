#include <fenv.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(fenv_t)
T(fexcept_t)
//FE_DIVBYZERO
//FE_INEXACT
//FE_INVALID
//FE_OVERFLOW
//FE_UNDERFLOW
C(FE_ALL_EXCEPT)
//FE_DOWNWARD
//FE_TONEAREST
//FE_TOWARDZERO
//FE_UPWARD
{const fenv_t *c = FE_DFL_ENV;}
int(*p_feclearexcept)(int) = feclearexcept;
int(*p_fegetenv)(fenv_t*) = fegetenv;
int(*p_fegetexceptflag)(fexcept_t*,int) = fegetexceptflag;
int(*p_fegetround)(void) = fegetround;
int(*p_feholdexcept)(fenv_t*) = feholdexcept;
int(*p_feraiseexcept)(int) = feraiseexcept;
int(*p_fesetenv)(const fenv_t*) = fesetenv;
int(*p_fesetexceptflag)(const fexcept_t*,int) = fesetexceptflag;
int(*p_fesetround)(int) = fesetround;
int(*p_fetestexcept)(int) = fetestexcept;
int(*p_feupdateenv)(const fenv_t*) = feupdateenv;
}
