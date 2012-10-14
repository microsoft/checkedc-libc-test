#include <dirent.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(DIR)
T(struct dirent)
#ifdef _XOPEN_SOURCE
T(ino_t)
#endif
{
struct dirent x;
#ifdef _XOPEN_SOURCE
F(ino_t,  d_ino)
#endif
F(char,   d_name[0])
}
int(*p_alphasort)(const struct dirent**,const struct dirent**) = alphasort;
int(*p_closedir)(DIR*) = closedir;
int(*p_dirfd)(DIR*) = dirfd;
DIR*(*p_fdopendir)(int) = fdopendir;
DIR*(*p_opendir)(const char*) = opendir;
struct dirent*(*p_readdir)(DIR*) = readdir;
int(*p_readdir_r)(DIR*restrict,struct dirent*restrict,struct dirent**restrict) = readdir_r;
void(*p_rewinddir)(DIR*) = rewinddir;
int(*p_scandir)(const char*,struct dirent***,int(*)(const struct dirent*),int(*)(const struct dirent**,const struct dirent**)) = scandir;
#ifdef _XOPEN_SOURCE
void(*p_seekdir)(DIR*,long) = seekdir;
long(*p_telldir)(DIR*) = telldir;
#endif
}
