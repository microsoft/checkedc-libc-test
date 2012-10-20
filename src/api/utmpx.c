#include <utmpx.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(pid_t)
T(struct timeval)
{
struct utmpx x;
F(char,ut_user[0])
F(char,ut_id[0])
F(char,ut_line[0])
F(pid_t, ut_pid)
F(short, ut_type)
F(struct timeval,ut_tv)
}
C(EMPTY)
C(BOOT_TIME)
C(OLD_TIME)
C(NEW_TIME)
C(USER_PROCESS)
C(INIT_PROCESS)
C(LOGIN_PROCESS)
C(DEAD_PROCESS)
void(*p_endutxent)(void) = endutxent;
struct utmpx*(*p_getutxent)(void) = getutxent;
struct utmpx*(*p_getutxid)(const struct utmpx*) = getutxid;
struct utmpx*(*p_getutxline)(const struct utmpx*) = getutxline;
struct utmpx*(*p_pututxline)(const struct utmpx*) = pututxline;
void(*p_setutxent)(void) = setutxent;
}
