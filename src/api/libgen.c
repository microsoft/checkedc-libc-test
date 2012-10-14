#ifdef _XOPEN_SOURCE
#include <libgen.h>
static void f()
{
char*(*p_basename)(char*) = basename;
char*(*p_dirname)(char*) = dirname;
}
#endif

