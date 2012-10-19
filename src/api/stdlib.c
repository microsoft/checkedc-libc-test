#include <stdlib.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
C(EXIT_FAILURE)
C(EXIT_SUCCESS)
C(RAND_MAX)
C(MB_CUR_MAX)
{void *x=NULL;}
T(div_t)
T(ldiv_t)
T(lldiv_t)
T(size_t)
T(wchar_t)
#ifdef _POSIX_C_SOURCE
C(WEXITSTATUS(0))
C(WIFEXITED(0))
C(WIFSIGNALED(0))
C(WIFSTOPPED(0))
C(WNOHANG)
C(WSTOPSIG(0))
C(WTERMSIG(0))
C(WUNTRACED)
#endif
void(*p__Exit)(int) = _Exit;
void(*p_abort)(void) = abort;
int(*p_abs)(int) = abs;
int(*p_atexit)(void(*)(void)) = atexit;
double(*p_atof)(const char*) = atof;
int(*p_atoi)(const char*) = atoi;
long(*p_atol)(const char*) = atol;
long long(*p_atoll)(const char*) = atoll;
void*(*p_bsearch)(const void*,const void*,size_t,size_t,int(*)(const void*,const void*)) = bsearch;
void*(*p_calloc)(size_t,size_t) = calloc;
div_t(*p_div)(int,int) = div;
void(*p_exit)(int) = exit;
void(*p_free)(void*) = free;
char*(*p_getenv)(const char*) = getenv;
int(*p_getsubopt)(char**,char*const*,char**) = getsubopt;
long(*p_labs)(long) = labs;
ldiv_t(*p_ldiv)(long,long) = ldiv;
long long(*p_llabs)(long long) = llabs;
lldiv_t(*p_lldiv)(long long,long long) = lldiv;
void*(*p_malloc)(size_t) = malloc;
int(*p_mblen)(const char*,size_t) = mblen;
size_t(*p_mbstowcs)(wchar_t*restrict,const char*restrict,size_t) = mbstowcs;
int(*p_mbtowc)(wchar_t*restrict,const char*restrict,size_t) = mbtowc;
int(*p_posix_memalign)(void**,size_t,size_t) = posix_memalign;
void(*p_qsort)(void*,size_t,size_t,int(*)(const void*,const void*)) = qsort;
int(*p_rand)(void) = rand;
void*(*p_realloc)(void*,size_t) = realloc;
void(*p_srand)(unsigned) = srand;
double(*p_strtod)(const char*restrict,char**restrict) = strtod;
float(*p_strtof)(const char*restrict,char**restrict) = strtof;
long(*p_strtol)(const char*restrict,char**restrict,int) = strtol;
long double(*p_strtold)(const char*restrict,char**restrict) = strtold;
long long(*p_strtoll)(const char*restrict,char**restrict,int) = strtoll;
unsigned long(*p_strtoul)(const char*restrict,char**restrict,int) = strtoul;
unsigned long long(*p_strtoull)(const char*restrict,char**restrict,int) = strtoull;
int(*p_system)(const char*) = system;
size_t(*p_wcstombs)(char*restrict,const wchar_t*restrict,size_t) = wcstombs;
int(*p_wctomb)(char*,wchar_t) = wctomb;
#ifdef _POSIX_C_SOURCE
char*(*p_mkdtemp)(char*) = mkdtemp;
int(*p_mkstemp)(char*) = mkstemp;
int(*p_setenv)(const char*,const char*,int) = setenv;
int(*p_unsetenv)(const char*) = unsetenv;
#endif
#ifdef _XOPEN_SOURCE
long(*p_a64l)(const char*) = a64l;
double(*p_drand48)(void) = drand48;
double(*p_erand48)(unsigned short[]) = erand48;
int(*p_grantpt)(int) = grantpt;
char*(*p_initstate)(unsigned,char*,size_t) = initstate;
long(*p_jrand48)(unsigned short[]) = jrand48;
char*(*p_l64a)(long) = l64a;
void(*p_lcong48)(unsigned short[]) = lcong48;
long(*p_lrand48)(void) = lrand48;
long(*p_mrand48)(void) = mrand48;
long(*p_nrand48)(unsigned short[]) = nrand48;
char*(*p_ptsname)(int) = ptsname;
int(*p_putenv)(char*) = putenv;
long(*p_random)(void) = random;
char*(*p_realpath)(const char*restrict,char*restrict) = realpath;
unsigned short*(*p_seed48)(unsigned short[]) = seed48;
void(*p_setkey)(const char*) = setkey;
char*(*p_setstate)(char*) = setstate;
void(*p_srand48)(long) = srand48;
void(*p_srandom)(unsigned) = srandom;
int(*p_unlockpt)(int) = unlockpt;
#endif
}

#ifdef _XOPEN_SOURCE
#include <fcntl.h>
static void g()
{
int(*p_posix_openpt)(int) = posix_openpt;
}
#endif

