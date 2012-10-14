#include <pwd.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
static void f()
{
T(gid_t)
T(uid_t)
T(size_t)
{
struct passwd x;
F(char*,pw_name)
F(uid_t,pw_uid)
F(gid_t,pw_gid)
F(char*,pw_dir)
F(char*,pw_shell)
}
struct passwd*(*p_getpwnam)(const char*) = getpwnam;
int(*p_getpwnam_r)(const char*,struct passwd*,char*,size_t,struct passwd**) = getpwnam_r;
struct passwd*(*p_getpwuid)(uid_t) = getpwuid;
int(*p_getpwuid_r)(uid_t,struct passwd*,char*,size_t,struct passwd**) = getpwuid_r;
#ifdef _XOPEN_SOURCE
void(*p_endpwent)(void) = endpwent;
struct passwd*(*p_getpwent)(void) = getpwent;
void(*p_setpwent)(void) = setpwent;
#endif
}
