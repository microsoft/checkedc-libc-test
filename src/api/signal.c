#include <signal.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(sig_atomic_t)
{void(*x)(int) = SIG_DFL;}
{void(*x)(int) = SIG_ERR;}
{void(*x)(int) = SIG_IGN;}
#ifdef _POSIX_C_SOURCE
{void(*x)(int) = SIG_HOLD;}
T(size_t)
T(sigset_t)
T(pid_t)
T(uid_t)
T(pthread_t)
T(pthread_attr_t)
T(struct timespec)
{
struct sigevent x;
F(int,sigev_notify)
F(int,sigev_signo)
F(union sigval,sigev_value)
{void (**y)(union sigval) = &x.sigev_notify_function;}
F(pthread_attr_t*,sigev_notify_attributes)
}
C(SIGEV_NONE)
C(SIGEV_SIGNAL)
C(SIGEV_THREAD)
{
union sigval x;
F(int,sival_int)
F(void*,sival_ptr)
}
{int i = SIGRTMIN;}
{int i = SIGRTMAX;}
#endif
C(SIGABRT)
C(SIGFPE)
C(SIGILL)
C(SIGINT)
C(SIGSEGV)
C(SIGTERM)
#ifdef _POSIX_C_SOURCE
C(SIGALRM)
C(SIGBUS)
C(SIGCHLD)
C(SIGCONT)
C(SIGHUP)
C(SIGKILL)
C(SIGPIPE)
C(SIGQUIT)
C(SIGSTOP)
C(SIGTSTP)
C(SIGTTIN)
C(SIGTTOU)
C(SIGUSR1)
C(SIGUSR2)
C(SIGURG)
#ifdef _XOPEN_SOURCE
C(SIGSYS)
C(SIGTRAP)
C(SIGVTALRM)
C(SIGXCPU)
C(SIGXFSZ)
#endif
{
struct sigaction x;
{void (**y)(int) = &x.sa_handler;}
F(sigset_t, sa_mask)
F(int,sa_flags)
{void (**y)(int, siginfo_t *, void *) = &x.sa_sigaction;}
}
C(SIG_BLOCK)
C(SIG_UNBLOCK)
C(SIG_SETMASK)
C(SA_NOCLDSTOP)
C(SA_RESETHAND)
C(SA_RESTART)
C(SA_SIGINFO)
C(SA_NOCLDWAIT)
C(SA_NODEFER)
#ifdef _XOPEN_SOURCE
C(SA_ONSTACK)
C(SS_ONSTACK)
C(SS_DISABLE)
C(MINSIGSTKSZ)
C(SIGSTKSZ)
#endif
T(mcontext_t)
{
ucontext_t x;
F(ucontext_t*,uc_link)
F(sigset_t,uc_sigmask)
F(stack_t, uc_stack)
F(mcontext_t,uc_mcontext)
}
{
stack_t x;
F(void *,ss_sp)
F(size_t,ss_size)
F(int, ss_flags)
}
{
siginfo_t x;
F(int, si_signo)
F(int, si_code)
#ifdef _XOPEN_SOURCE
F(int, si_errno)
#endif
F(pid_t, si_pid)
F(uid_t, si_uid)
F(void *,si_addr)
F(int, si_status)
F(union sigval,si_value)
}
C(ILL_ILLOPC)
C(ILL_ILLOPN)
C(ILL_ILLADR)
C(ILL_ILLTRP)
C(ILL_PRVOPC)
C(ILL_PRVREG)
C(ILL_COPROC)
C(ILL_BADSTK)
C(FPE_INTDIV)
C(FPE_INTOVF)
C(FPE_FLTDIV)
C(FPE_FLTOVF)
C(FPE_FLTUND)
C(FPE_FLTRES)
C(FPE_FLTINV)
C(FPE_FLTSUB)
C(SEGV_MAPERR)
C(SEGV_ACCERR)
C(BUS_ADRALN)
C(BUS_ADRERR)
C(BUS_OBJERR)
#ifdef _XOPEN_SOURCE
C(TRAP_BRKPT)
C(TRAP_TRACE)
#endif
C(CLD_EXITED)
C(CLD_KILLED)
C(CLD_DUMPED)
C(CLD_TRAPPED)
C(CLD_STOPPED)
C(CLD_CONTINUED)
C(SI_USER)
C(SI_QUEUE)
C(SI_TIMER)
C(SI_ASYNCIO)
C(SI_MESGQ)
int(*p_kill)(pid_t,int) = kill;
int(*p_killpg)(pid_t,int) = killpg;
void(*p_psiginfo)(const siginfo_t*,const char*) = psiginfo;
void(*p_psignal)(int,const char*) = psignal;
int(*p_pthread_kill)(pthread_t,int) = pthread_kill;
int(*p_pthread_sigmask)(int,const sigset_t*restrict,sigset_t*restrict) = pthread_sigmask;
int(*p_sigaction)(int,const struct sigaction*restrict,struct sigaction*restrict) = sigaction;
int(*p_sigaddset)(sigset_t*,int) = sigaddset;
int(*p_sigaltstack)(const stack_t*restrict,stack_t*restrict) = sigaltstack;
int(*p_sigdelset)(sigset_t*,int) = sigdelset;
int(*p_sigemptyset)(sigset_t*) = sigemptyset;
int(*p_sigfillset)(sigset_t*) = sigfillset;
int(*p_sighold)(int) = sighold;
int(*p_sigignore)(int) = sigignore;
int(*p_siginterrupt)(int,int) = siginterrupt;
int(*p_sigismember)(const sigset_t*,int) = sigismember;
int(*p_sigpause)(int) = sigpause;
int(*p_sigpending)(sigset_t*) = sigpending;
int(*p_sigprocmask)(int,const sigset_t*restrict,sigset_t*restrict) = sigprocmask;
int(*p_sigqueue)(pid_t,int,const union sigval) = sigqueue;
int(*p_sigrelse)(int) = sigrelse;
void(*(*p_sigset)(int,void(*)(int)))(int) = sigset;
int(*p_sigsuspend)(const sigset_t*) = sigsuspend;
int(*p_sigtimedwait)(const sigset_t*restrict,siginfo_t*restrict,const struct timespec*restrict) = sigtimedwait;
int(*p_sigwait)(const sigset_t*restrict,int*restrict) = sigwait;
int(*p_sigwaitinfo)(const sigset_t*restrict,siginfo_t*restrict) = sigwaitinfo;
#endif
int(*p_raise)(int) = raise;
void(*(*p_signal)(int,void(*)(int)))(int) = signal;
}
