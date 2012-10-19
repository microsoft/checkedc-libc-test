#include <string.h>
#define T(t) (t*)0;
static void f()
{
T(size_t)
void*(*p_memchr)(const void*,int,size_t) = memchr;
int(*p_memcmp)(const void*,const void*,size_t) = memcmp;
void*(*p_memcpy)(void*restrict,const void*restrict,size_t) = memcpy;
void*(*p_memmove)(void*,const void*,size_t) = memmove;
void*(*p_memset)(void*,int,size_t) = memset;
char*(*p_strcat)(char*restrict,const char*restrict) = strcat;
char*(*p_strchr)(const char*,int) = strchr;
int(*p_strcmp)(const char*,const char*) = strcmp;
int(*p_strcoll)(const char*,const char*) = strcoll;
char*(*p_strcpy)(char*restrict,const char*restrict) = strcpy;
size_t(*p_strcspn)(const char*,const char*) = strcspn;
char*(*p_strerror)(int) = strerror;
size_t(*p_strlen)(const char*) = strlen;
char*(*p_strncat)(char*restrict,const char*restrict,size_t) = strncat;
int(*p_strncmp)(const char*,const char*,size_t) = strncmp;
char*(*p_strncpy)(char*restrict,const char*restrict,size_t) = strncpy;
char*(*p_strpbrk)(const char*,const char*) = strpbrk;
char*(*p_strrchr)(const char*,int) = strrchr;
char*(*p_strsignal)(int) = strsignal;
size_t(*p_strspn)(const char*,const char*) = strspn;
char*(*p_strstr)(const char*,const char*) = strstr;
char*(*p_strtok)(char*restrict,const char*restrict) = strtok;
size_t(*p_strxfrm)(char*restrict,const char*restrict,size_t) = strxfrm;
#ifdef _POSIX_C_SOURCE
T(locale_t)
char*(*p_stpcpy)(char*restrict,const char*restrict) = stpcpy;
char*(*p_stpncpy)(char*restrict,const char*restrict,size_t) = stpncpy;
int(*p_strcoll_l)(const char*,const char*,locale_t) = strcoll_l;
char*(*p_strdup)(const char*) = strdup;
char*(*p_strerror_l)(int,locale_t) = strerror_l;
int(*p_strerror_r)(int,char*,size_t) = strerror_r;
char*(*p_strndup)(const char*,size_t) = strndup;
size_t(*p_strnlen)(const char*,size_t) = strnlen;
char*(*p_strtok_r)(char*restrict,const char*restrict,char**restrict) = strtok_r;
size_t(*p_strxfrm_l)(char*restrict,const char*restrict,size_t,locale_t) = strxfrm_l;
#endif
#ifdef _XOPEN_SOURCE
void*(*p_memccpy)(void*restrict,const void*restrict,int,size_t) = memccpy;
#endif
}
