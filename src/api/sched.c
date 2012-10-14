#include <sched.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(pid_t)
T(time_t)
T(struct timespec)
{
struct sched_param x;
F(int,sched_priority)
F(int,sched_ss_low_priority)
F(struct timespec,sched_ss_repl_period)
F(struct timespec,sched_ss_init_budget)
F(int,sched_ss_max_repl)
}
C(SCHED_FIFO)
C(SCHED_RR)
C(SCHED_SPORADIC)
C(SCHED_OTHER)
int(*p_sched_get_priority_max)(int) = sched_get_priority_max;
int(*p_sched_get_priority_min)(int) = sched_get_priority_min;
int(*p_sched_getparam)(pid_t,struct sched_param*) = sched_getparam;
int(*p_sched_getscheduler)(pid_t) = sched_getscheduler;
int(*p_sched_rr_get_interval)(pid_t,struct timespec*) = sched_rr_get_interval;
int(*p_sched_setparam)(pid_t,const struct sched_param*) = sched_setparam;
int(*p_sched_setscheduler)(pid_t,int,const struct sched_param*) = sched_setscheduler;
int(*p_sched_yield)(void) = sched_yield;
}
