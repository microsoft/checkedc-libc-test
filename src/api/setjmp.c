#include <setjmp.h>
#define T(t) (t*)0;
static void f()
{
T(jmp_buf)
void(*p_longjmp)(jmp_buf,int) = longjmp;
int(*p_setjmp)(jmp_buf) = setjmp;
#ifdef _POSIX_C_SOURCE
T(sigjmp_buf)
void(*p_siglongjmp)(sigjmp_buf,int) = siglongjmp;
int(*p_sigsetjmp)(sigjmp_buf,int) = sigsetjmp;
#endif
}
