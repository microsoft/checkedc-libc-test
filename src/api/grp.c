#include <grp.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
static void f()
{
T(gid_t)
T(size_t)
{
struct group x;
F(char*, gr_name)
F(gid_t, gr_gid)
F(char**, gr_mem)
}
void(*p_endgrent)(void) = endgrent;
struct group*(*p_getgrent)(void) = getgrent;
struct group*(*p_getgrgid)(gid_t) = getgrgid;
int(*p_getgrgid_r)(gid_t,struct group*,char*,size_t,struct group**) = getgrgid_r;
struct group*(*p_getgrnam)(const char*) = getgrnam;
int(*p_getgrnam_r)(const char*,struct group*,char*,size_t,struct group**) = getgrnam_r;
#ifdef _XOPEN_SOURCE
void(*p_setgrent)(void) = setgrent;
#endif
}
