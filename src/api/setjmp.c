#include <setjmp.h>
#define T(t) (t*)0;
static void f()
{
T(jmp_buf)
{void(*p)(jmp_buf,int) = longjmp;}
{int(*p)(jmp_buf) = setjmp;}
#ifdef _POSIX_C_SOURCE
T(sigjmp_buf)
{void(*p)(sigjmp_buf,int) = siglongjmp;}
{int(*p)(sigjmp_buf,int) = sigsetjmp;}
#endif
#if defined _XOPEN_SOURCE && defined OBSOLETE
{void(*p)(jmp_buf,int) = _longjmp;}
{int(*p)(jmp_buf) = _setjmp;}
#endif
}
