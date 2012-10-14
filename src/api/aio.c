#include <aio.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(off_t)
T(pthread_attr_t)
T(size_t)
T(ssize_t)
T(struct timespec)

{
struct aiocb x;
F(int,             aio_fildes)
F(off_t,           aio_offset)
F(volatile void *, aio_buf)
F(size_t,          aio_nbytes)
F(int,             aio_reqprio)
F(struct sigevent, aio_sigevent)
F(int,             aio_lio_opcode)
}

C(AIO_ALLDONE)
C(AIO_CANCELED)
C(AIO_NOTCANCELED)
C(LIO_NOP)
C(LIO_NOWAIT)
C(LIO_READ)
C(LIO_WAIT)
C(LIO_WRITE)

int(*p_aio_cancel)(int,struct aiocb*) = aio_cancel;
int(*p_aio_error)(const struct aiocb*) = aio_error;
int(*p_aio_fsync)(int,struct aiocb*) = aio_fsync;
int(*p_aio_read)(struct aiocb*) = aio_read;
ssize_t(*p_aio_return)(struct aiocb*) = aio_return;
int(*p_aio_suspend)(const struct aiocb*const[],int,const struct timespec*) = aio_suspend;
int(*p_aio_write)(struct aiocb*) = aio_write;
int(*p_lio_listio)(int,struct aiocb*restrict const[restrict],int,struct sigevent*restrict) = lio_listio;
}
