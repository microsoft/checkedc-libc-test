#include <semaphore.h>
static void f()
{
{sem_t *x = SEM_FAILED;}
int(*p_sem_close)(sem_t*) = sem_close;
int(*p_sem_destroy)(sem_t*) = sem_destroy;
int(*p_sem_getvalue)(sem_t*restrict,int*restrict) = sem_getvalue;
int(*p_sem_init)(sem_t*,int,unsigned) = sem_init;
sem_t*(*p_sem_open)(const char*,int,...) = sem_open;
int(*p_sem_post)(sem_t*) = sem_post;
int(*p_sem_trywait)(sem_t*) = sem_trywait;
int(*p_sem_unlink)(const char*) = sem_unlink;
int(*p_sem_wait)(sem_t*) = sem_wait;
}
#include <time.h>
static void g()
{
int(*p_sem_timedwait)(sem_t*restrict,const struct timespec*restrict) = sem_timedwait;
}
