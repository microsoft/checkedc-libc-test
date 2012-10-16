#include <mqueue.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
static void f()
{
T(mqd_t)
T(pthread_attr_t)
T(size_t)
T(ssize_t)
T(struct timespec)
T(struct sigevent)
{
struct mq_attr x;
F(long, mq_flags)
F(long, mq_maxmsg)
F(long, mq_msgsize)
F(long, mq_curmsgs)
}
int(*p_mq_close)(mqd_t) = mq_close;
int(*p_mq_getattr)(mqd_t,struct mq_attr*) = mq_getattr;
int(*p_mq_notify)(mqd_t,const struct sigevent*) = mq_notify;
mqd_t(*p_mq_open)(const char*,int,...) = mq_open;
ssize_t(*p_mq_receive)(mqd_t,char*,size_t,unsigned*) = mq_receive;
int(*p_mq_send)(mqd_t,const char*,size_t,unsigned) = mq_send;
int(*p_mq_setattr)(mqd_t,const struct mq_attr*restrict,struct mq_attr*restrict) = mq_setattr;
int(*p_mq_unlink)(const char*) = mq_unlink;
}
#include <time.h>
static void g()
{
ssize_t(*p_mq_timedreceive)(mqd_t,char*restrict,size_t,unsigned*restrict,const struct timespec*restrict) = mq_timedreceive;
int(*p_mq_timedsend)(mqd_t,const char*,size_t,unsigned,const struct timespec*) = mq_timedsend;
}
