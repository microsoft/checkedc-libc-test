#include <dlfcn.h>
#define C(n) switch(n){case n:;}
static void f()
{
C(RTLD_LAZY)
C(RTLD_NOW)
C(RTLD_GLOBAL)
C(RTLD_LOCAL)

int(*p_dlclose)(void*) = dlclose;
char*(*p_dlerror)(void) = dlerror;
void*(*p_dlopen)(const char*,int) = dlopen;
void*(*p_dlsym)(void*restrict,const char*restrict) = dlsym;
}
