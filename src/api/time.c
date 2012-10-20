#include <time.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(clock_t)
T(size_t)
T(time_t)
#ifdef _POSIX_C_SOURCE
T(clockid_t)
T(timer_t)
T(locale_t)
T(pid_t)
T(struct sigevent)
{
struct timespec x;
F(time_t,tv_sec)
F(long,tv_nsec)
}
{
struct itimerspec x;
F(struct timespec,it_interval)
F(struct timespec,it_value)
}
C(CLOCK_MONOTONIC)
C(CLOCK_PROCESS_CPUTIME_ID)
C(CLOCK_REALTIME)
C(CLOCK_THREAD_CPUTIME_ID)
#endif
{
struct tm x;
F(int,tm_sec)
F(int,tm_min)
F(int,tm_hour)
F(int,tm_mday)
F(int,tm_mon)
F(int,tm_year)
F(int,tm_wday)
F(int,tm_yday)
F(int,tm_isdst)
}
{void *x = NULL;}
{int x = CLOCKS_PER_SEC;}
C(TIMER_ABSTIME)
char*(*p_asctime)(const struct tm*) = asctime;
clock_t(*p_clock)(void) = clock;
char*(*p_ctime)(const time_t*) = ctime;
{int i = daylight;}
double(*p_difftime)(time_t,time_t) = difftime;
struct tm*(*p_gmtime)(const time_t*) = gmtime;
struct tm*(*p_localtime)(const time_t*) = localtime;
time_t(*p_mktime)(struct tm*) = mktime;
size_t(*p_strftime)(char*restrict,size_t,const char*restrict,const struct tm*restrict) = strftime;
time_t(*p_time)(time_t*) = time;
#ifdef _POSIX_C_SOURCE
char*(*p_asctime_r)(const struct tm*restrict,char*restrict) = asctime_r;
int(*p_clock_getcpuclockid)(pid_t,clockid_t*) = clock_getcpuclockid;
int(*p_clock_getres)(clockid_t,struct timespec*) = clock_getres;
int(*p_clock_gettime)(clockid_t,struct timespec*) = clock_gettime;
int(*p_clock_nanosleep)(clockid_t,int,const struct timespec*,struct timespec*) = clock_nanosleep;
int(*p_clock_settime)(clockid_t,const struct timespec*) = clock_settime;
char*(*p_ctime_r)(const time_t*,char*) = ctime_r;
struct tm*(*p_gmtime_r)(const time_t*restrict,struct tm*restrict) = gmtime_r;
struct tm*(*p_localtime_r)(const time_t*restrict,struct tm*restrict) = localtime_r;
int(*p_nanosleep)(const struct timespec*,struct timespec*) = nanosleep;
size_t(*p_strftime_l)(char*restrict,size_t,const char*restrict,const struct tm*restrict,locale_t) = strftime_l;
int(*p_timer_delete)(timer_t) = timer_delete;
int(*p_timer_getoverrun)(timer_t) = timer_getoverrun;
int(*p_timer_gettime)(timer_t,struct itimerspec*) = timer_gettime;
int(*p_timer_settime)(timer_t,int,const struct itimerspec*restrict,struct itimerspec*restrict) = timer_settime;
{char **x = tzname;}
void(*p_tzset)(void) = tzset;
#endif
#ifdef _XOPEN_SOURCE
struct tm*(*p_getdate)(const char*) = getdate;
{int i = getdate_err;}
char*(*p_strptime)(const char*restrict,const char*restrict,struct tm*restrict) = strptime;
{long i = timezone;}
#endif
}
#ifdef _POSIX_C_SOURCE
#include <signal.h>
static void g()
{
int(*p_timer_create)(clockid_t,struct sigevent*restrict,timer_t*restrict) = timer_create;
}
#endif
