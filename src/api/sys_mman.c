#include <sys/mman.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(mode_t)
T(off_t)
T(size_t)
C(PROT_EXEC)
C(PROT_NONE)
C(PROT_READ)
C(PROT_WRITE)
C(MAP_FIXED)
C(MAP_PRIVATE)
C(MAP_SHARED)
#ifdef _XOPEN_SOURCE
C(MS_ASYNC)
C(MS_INVALIDATE)
C(MS_SYNC)
#endif
C(MCL_CURRENT)
C(MCL_FUTURE)
{void *x = MAP_FAILED;}
C(POSIX_MADV_DONTNEED)
C(POSIX_MADV_NORMAL)
C(POSIX_MADV_RANDOM)
C(POSIX_MADV_SEQUENTIAL)
C(POSIX_MADV_WILLNEED)
//C(POSIX_TYPED_MEM_ALLOCATE)
//C(POSIX_TYPED_MEM_ALLOCATE_CONTIG)
//C(POSIX_TYPED_MEM_MAP_ALLOCATABLE)
//{
//struct posix_typed_mem_info x;
//F(size_t,posix_tmi_length)
//}
int(*p_mlock)(const void*,size_t) = mlock;
int(*p_mlockall)(int) = mlockall;
void*(*p_mmap)(void*,size_t,int,int,int,off_t) = mmap;
int(*p_mprotect)(void*,size_t,int) = mprotect;
#ifdef _XOPEN_SOURCE
int(*p_msync)(void*,size_t,int) = msync;
#endif
int(*p_munlock)(const void*,size_t) = munlock;
int(*p_munlockall)(void) = munlockall;
int(*p_munmap)(void*,size_t) = munmap;
int(*p_posix_madvise)(void*,size_t,int) = posix_madvise;
//int(*p_posix_mem_offset)(const void*restrict,size_t,off_t*restrict,size_t*restrict,int*restrict) = posix_mem_offset;
//int(*p_posix_typed_mem_get_info)(int,struct posix_typed_mem_info*) = posix_typed_mem_get_info;
//int(*p_posix_typed_mem_open)(const char*,int,int) = posix_typed_mem_open;
int(*p_shm_open)(const char*,int,mode_t) = shm_open;
int(*p_shm_unlink)(const char*) = shm_unlink;
}
