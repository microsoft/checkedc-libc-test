#include <pthread.h>
#define T(t) (t*)0;
#define C(n) switch(n){case n:;}
static void f()
{
T(pthread_attr_t)
T(pthread_barrier_t)
T(pthread_barrierattr_t)
T(pthread_cond_t)
T(pthread_condattr_t)
T(pthread_key_t)
T(pthread_mutex_t)
T(pthread_mutexattr_t)
T(pthread_once_t)
T(pthread_rwlock_t)
T(pthread_rwlockattr_t)
T(pthread_spinlock_t)
T(pthread_t)
C(PTHREAD_BARRIER_SERIAL_THREAD)
C(PTHREAD_CANCEL_ASYNCHRONOUS)
C(PTHREAD_CANCEL_ENABLE)
C(PTHREAD_CANCEL_DEFERRED)
C(PTHREAD_CANCEL_DISABLE)
{void *x = PTHREAD_CANCELED;}
C(PTHREAD_CREATE_DETACHED)
C(PTHREAD_CREATE_JOINABLE)
C(PTHREAD_EXPLICIT_SCHED)
C(PTHREAD_INHERIT_SCHED)
C(PTHREAD_MUTEX_DEFAULT)
C(PTHREAD_MUTEX_ERRORCHECK)
C(PTHREAD_MUTEX_NORMAL)
C(PTHREAD_MUTEX_RECURSIVE)
C(PTHREAD_MUTEX_ROBUST)
C(PTHREAD_MUTEX_STALLED)
C(PTHREAD_ONCE_INIT)
C(PTHREAD_PRIO_INHERIT)
C(PTHREAD_PRIO_NONE)
C(PTHREAD_PRIO_PROTECT)
C(PTHREAD_PROCESS_SHARED)
C(PTHREAD_PROCESS_PRIVATE)
C(PTHREAD_SCOPE_PROCESS)
C(PTHREAD_SCOPE_SYSTEM)
{pthread_cond_t x = PTHREAD_COND_INITIALIZER;}
{pthread_mutex_t x = PTHREAD_MUTEX_INITIALIZER;}
{pthread_rwlock_t x = PTHREAD_RWLOCK_INITIALIZER;}
int(*p_pthread_atfork)(void(*)(void),void(*)(void),void(*)(void)) = pthread_atfork;
int(*p_pthread_attr_destroy)(pthread_attr_t*) = pthread_attr_destroy;
int(*p_pthread_attr_getdetachstate)(const pthread_attr_t*,int*) = pthread_attr_getdetachstate;
int(*p_pthread_attr_getguardsize)(const pthread_attr_t*restrict,size_t*restrict) = pthread_attr_getguardsize;
int(*p_pthread_attr_getinheritsched)(const pthread_attr_t*restrict,int*restrict) = pthread_attr_getinheritsched;
int(*p_pthread_attr_getschedparam)(const pthread_attr_t*restrict,struct sched_param*restrict) = pthread_attr_getschedparam;
int(*p_pthread_attr_getschedpolicy)(const pthread_attr_t*restrict,int*restrict) = pthread_attr_getschedpolicy;
int(*p_pthread_attr_getscope)(const pthread_attr_t*restrict,int*restrict) = pthread_attr_getscope;
int(*p_pthread_attr_getstack)(const pthread_attr_t*restrict,void**restrict,size_t*restrict) = pthread_attr_getstack;
int(*p_pthread_attr_getstacksize)(const pthread_attr_t*restrict,size_t*restrict) = pthread_attr_getstacksize;
int(*p_pthread_attr_init)(pthread_attr_t*) = pthread_attr_init;
int(*p_pthread_attr_setdetachstate)(pthread_attr_t*,int) = pthread_attr_setdetachstate;
int(*p_pthread_attr_setguardsize)(pthread_attr_t*,size_t) = pthread_attr_setguardsize;
int(*p_pthread_attr_setinheritsched)(pthread_attr_t*,int) = pthread_attr_setinheritsched;
int(*p_pthread_attr_setschedparam)(pthread_attr_t*restrict,const struct sched_param*restrict) = pthread_attr_setschedparam;
int(*p_pthread_attr_setschedpolicy)(pthread_attr_t*,int) = pthread_attr_setschedpolicy;
int(*p_pthread_attr_setscope)(pthread_attr_t*,int) = pthread_attr_setscope;
int(*p_pthread_attr_setstack)(pthread_attr_t*,void*,size_t) = pthread_attr_setstack;
int(*p_pthread_attr_setstacksize)(pthread_attr_t*,size_t) = pthread_attr_setstacksize;
int(*p_pthread_barrier_destroy)(pthread_barrier_t*) = pthread_barrier_destroy;
int(*p_pthread_barrier_init)(pthread_barrier_t*restrict,const pthread_barrierattr_t*restrict,unsigned) = pthread_barrier_init;
int(*p_pthread_barrier_wait)(pthread_barrier_t*) = pthread_barrier_wait;
int(*p_pthread_barrierattr_destroy)(pthread_barrierattr_t*) = pthread_barrierattr_destroy;
int(*p_pthread_barrierattr_getpshared)(const pthread_barrierattr_t*restrict,int*restrict) = pthread_barrierattr_getpshared;
int(*p_pthread_barrierattr_init)(pthread_barrierattr_t*) = pthread_barrierattr_init;
int(*p_pthread_barrierattr_setpshared)(pthread_barrierattr_t*,int) = pthread_barrierattr_setpshared;
int(*p_pthread_cancel)(pthread_t) = pthread_cancel;
void(*p_pthread_cleanup_pop)(int) = pthread_cleanup_pop;
void(*p_pthread_cleanup_push)(void(*)(void*),void*) = pthread_cleanup_push;
int(*p_pthread_cond_broadcast)(pthread_cond_t*) = pthread_cond_broadcast;
int(*p_pthread_cond_destroy)(pthread_cond_t*) = pthread_cond_destroy;
int(*p_pthread_cond_init)(pthread_cond_t*restrict,const pthread_condattr_t*restrict) = pthread_cond_init;
int(*p_pthread_cond_signal)(pthread_cond_t*) = pthread_cond_signal;
int(*p_pthread_cond_timedwait)(pthread_cond_t*restrict,pthread_mutex_t*restrict,const struct timespec*restrict) = pthread_cond_timedwait;
int(*p_pthread_cond_wait)(pthread_cond_t*restrict,pthread_mutex_t*restrict) = pthread_cond_wait;
int(*p_pthread_condattr_destroy)(pthread_condattr_t*) = pthread_condattr_destroy;
int(*p_pthread_condattr_getclock)(const pthread_condattr_t*restrict,clockid_t*restrict) = pthread_condattr_getclock;
int(*p_pthread_condattr_getpshared)(const pthread_condattr_t*restrict,int*restrict) = pthread_condattr_getpshared;
int(*p_pthread_condattr_init)(pthread_condattr_t*) = pthread_condattr_init;
int(*p_pthread_condattr_setclock)(pthread_condattr_t*,clockid_t) = pthread_condattr_setclock;
int(*p_pthread_condattr_setpshared)(pthread_condattr_t*,int) = pthread_condattr_setpshared;
int(*p_pthread_create)(pthread_t*restrict,const pthread_attr_t*restrict,void*(*)(void*),void*restrict) = pthread_create;
int(*p_pthread_detach)(pthread_t) = pthread_detach;
int(*p_pthread_equal)(pthread_t,pthread_t) = pthread_equal;
void(*p_pthread_exit)(void*) = pthread_exit;
int(*p_pthread_getschedparam)(pthread_t,int*restrict,struct sched_param*restrict) = pthread_getschedparam;
void*(*p_pthread_getspecific)(pthread_key_t) = pthread_getspecific;
int(*p_pthread_join)(pthread_t,void**) = pthread_join;
int(*p_pthread_key_create)(pthread_key_t*,void(*)(void*)) = pthread_key_create;
int(*p_pthread_key_delete)(pthread_key_t) = pthread_key_delete;
int(*p_pthread_mutex_consistent)(pthread_mutex_t*) = pthread_mutex_consistent;
int(*p_pthread_mutex_destroy)(pthread_mutex_t*) = pthread_mutex_destroy;
int(*p_pthread_mutex_getprioceiling)(const pthread_mutex_t*restrict,int*restrict) = pthread_mutex_getprioceiling;
int(*p_pthread_mutex_init)(pthread_mutex_t*restrict,const pthread_mutexattr_t*restrict) = pthread_mutex_init;
int(*p_pthread_mutex_lock)(pthread_mutex_t*) = pthread_mutex_lock;
int(*p_pthread_mutex_setprioceiling)(pthread_mutex_t*restrict,int,int*restrict) = pthread_mutex_setprioceiling;
int(*p_pthread_mutex_trylock)(pthread_mutex_t*) = pthread_mutex_trylock;
int(*p_pthread_mutex_unlock)(pthread_mutex_t*) = pthread_mutex_unlock;
int(*p_pthread_mutexattr_destroy)(pthread_mutexattr_t*) = pthread_mutexattr_destroy;
int(*p_pthread_mutexattr_getprioceiling)(const pthread_mutexattr_t*restrict,int*restrict) = pthread_mutexattr_getprioceiling;
int(*p_pthread_mutexattr_getprotocol)(const pthread_mutexattr_t*restrict,int*restrict) = pthread_mutexattr_getprotocol;
int(*p_pthread_mutexattr_getpshared)(const pthread_mutexattr_t*restrict,int*restrict) = pthread_mutexattr_getpshared;
int(*p_pthread_mutexattr_getrobust)(const pthread_mutexattr_t*restrict,int*restrict) = pthread_mutexattr_getrobust;
int(*p_pthread_mutexattr_gettype)(const pthread_mutexattr_t*restrict,int*restrict) = pthread_mutexattr_gettype;
int(*p_pthread_mutexattr_init)(pthread_mutexattr_t*) = pthread_mutexattr_init;
int(*p_pthread_mutexattr_setprioceiling)(pthread_mutexattr_t*,int) = pthread_mutexattr_setprioceiling;
int(*p_pthread_mutexattr_setprotocol)(pthread_mutexattr_t*,int) = pthread_mutexattr_setprotocol;
int(*p_pthread_mutexattr_setpshared)(pthread_mutexattr_t*,int) = pthread_mutexattr_setpshared;
int(*p_pthread_mutexattr_setrobust)(pthread_mutexattr_t*,int) = pthread_mutexattr_setrobust;
int(*p_pthread_mutexattr_settype)(pthread_mutexattr_t*,int) = pthread_mutexattr_settype;
int(*p_pthread_once)(pthread_once_t*,void(*)(void)) = pthread_once;
int(*p_pthread_rwlock_destroy)(pthread_rwlock_t*) = pthread_rwlock_destroy;
int(*p_pthread_rwlock_init)(pthread_rwlock_t*restrict,const pthread_rwlockattr_t*restrict) = pthread_rwlock_init;
int(*p_pthread_rwlock_rdlock)(pthread_rwlock_t*) = pthread_rwlock_rdlock;
int(*p_pthread_rwlock_tryrdlock)(pthread_rwlock_t*) = pthread_rwlock_tryrdlock;
int(*p_pthread_rwlock_trywrlock)(pthread_rwlock_t*) = pthread_rwlock_trywrlock;
int(*p_pthread_rwlock_unlock)(pthread_rwlock_t*) = pthread_rwlock_unlock;
int(*p_pthread_rwlock_wrlock)(pthread_rwlock_t*) = pthread_rwlock_wrlock;
int(*p_pthread_rwlockattr_destroy)(pthread_rwlockattr_t*) = pthread_rwlockattr_destroy;
int(*p_pthread_rwlockattr_getpshared)(const pthread_rwlockattr_t*restrict,int*restrict) = pthread_rwlockattr_getpshared;
int(*p_pthread_rwlockattr_init)(pthread_rwlockattr_t*) = pthread_rwlockattr_init;
int(*p_pthread_rwlockattr_setpshared)(pthread_rwlockattr_t*,int) = pthread_rwlockattr_setpshared;
pthread_t(*p_pthread_self)(void) = pthread_self;
int(*p_pthread_setcancelstate)(int,int*) = pthread_setcancelstate;
int(*p_pthread_setcanceltype)(int,int*) = pthread_setcanceltype;
int(*p_pthread_setschedparam)(pthread_t,int,const struct sched_param*) = pthread_setschedparam;
int(*p_pthread_setschedprio)(pthread_t,int) = pthread_setschedprio;
int(*p_pthread_setspecific)(pthread_key_t,const void*) = pthread_setspecific;
int(*p_pthread_spin_destroy)(pthread_spinlock_t*) = pthread_spin_destroy;
int(*p_pthread_spin_init)(pthread_spinlock_t*,int) = pthread_spin_init;
int(*p_pthread_spin_lock)(pthread_spinlock_t*) = pthread_spin_lock;
int(*p_pthread_spin_trylock)(pthread_spinlock_t*) = pthread_spin_trylock;
int(*p_pthread_spin_unlock)(pthread_spinlock_t*) = pthread_spin_unlock;
void(*p_pthread_testcancel)(void) = pthread_testcancel;
}
#include <time.h>
static void g()
{
int(*p_pthread_getcpuclockid)(pthread_t,clockid_t*) = pthread_getcpuclockid;
int(*p_pthread_mutex_timedlock)(pthread_mutex_t*restrict,const struct timespec*restrict) = pthread_mutex_timedlock;
int(*p_pthread_rwlock_timedrdlock)(pthread_rwlock_t*restrict,const struct timespec*restrict) = pthread_rwlock_timedrdlock;
int(*p_pthread_rwlock_timedwrlock)(pthread_rwlock_t*restrict,const struct timespec*restrict) = pthread_rwlock_timedwrlock;
}
