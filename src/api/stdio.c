#include <stdio.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(FILE)
T(fpos_t)
T(off_t)
T(size_t)
C(BUFSIZ)
#ifdef _POSIX_C_SOURCE
T(ssize_t)
T(va_list)
C(L_ctermid)
#endif
C(_IOFBF)
C(_IOLBF)
C(_IONBF)
C(SEEK_CUR)
C(SEEK_END)
C(SEEK_SET)
C(FILENAME_MAX)
C(FOPEN_MAX)
C(EOF)
{void *x=NULL;}
{FILE *x=stderr;}
{FILE *x=stdin;}
{FILE *x=stdout;}
void(*p_clearerr)(FILE*) = clearerr;
char*(*p_ctermid)(char*) = ctermid;
int(*p_dprintf)(int,const char*restrict,...) = dprintf;
int(*p_fclose)(FILE*) = fclose;
FILE*(*p_fdopen)(int,const char*) = fdopen;
int(*p_feof)(FILE*) = feof;
int(*p_ferror)(FILE*) = ferror;
int(*p_fflush)(FILE*) = fflush;
int(*p_fgetc)(FILE*) = fgetc;
int(*p_fgetpos)(FILE*restrict,fpos_t*restrict) = fgetpos;
char*(*p_fgets)(char*restrict,int,FILE*restrict) = fgets;
int(*p_fileno)(FILE*) = fileno;
void(*p_flockfile)(FILE*) = flockfile;
FILE*(*p_fmemopen)(void*restrict,size_t,const char*restrict) = fmemopen;
FILE*(*p_fopen)(const char*restrict,const char*restrict) = fopen;
int(*p_fprintf)(FILE*restrict,const char*restrict,...) = fprintf;
int(*p_fputc)(int,FILE*) = fputc;
int(*p_fputs)(const char*restrict,FILE*restrict) = fputs;
size_t(*p_fread)(void*restrict,size_t,size_t,FILE*restrict) = fread;
FILE*(*p_freopen)(const char*restrict,const char*restrict,FILE*restrict) = freopen;
int(*p_fscanf)(FILE*restrict,const char*restrict,...) = fscanf;
int(*p_fseek)(FILE*,long,int) = fseek;
int(*p_fseeko)(FILE*,off_t,int) = fseeko;
int(*p_fsetpos)(FILE*,const fpos_t*) = fsetpos;
long(*p_ftell)(FILE*) = ftell;
off_t(*p_ftello)(FILE*) = ftello;
int(*p_ftrylockfile)(FILE*) = ftrylockfile;
void(*p_funlockfile)(FILE*) = funlockfile;
size_t(*p_fwrite)(const void*restrict,size_t,size_t,FILE*restrict) = fwrite;
int(*p_getc)(FILE*) = getc;
int(*p_getc_unlocked)(FILE*) = getc_unlocked;
int(*p_getchar)(void) = getchar;
int(*p_getchar_unlocked)(void) = getchar_unlocked;
ssize_t(*p_getdelim)(char**restrict,size_t*restrict,int,FILE*restrict) = getdelim;
ssize_t(*p_getline)(char**restrict,size_t*restrict,FILE*restrict) = getline;
char*(*p_gets)(char*) = gets;
FILE*(*p_open_memstream)(char**,size_t*) = open_memstream;
int(*p_pclose)(FILE*) = pclose;
void(*p_perror)(const char*) = perror;
FILE*(*p_popen)(const char*,const char*) = popen;
int(*p_printf)(const char*restrict,...) = printf;
int(*p_putc)(int,FILE*) = putc;
int(*p_putc_unlocked)(int,FILE*) = putc_unlocked;
int(*p_putchar)(int) = putchar;
int(*p_putchar_unlocked)(int) = putchar_unlocked;
int(*p_puts)(const char*) = puts;
int(*p_remove)(const char*) = remove;
int(*p_rename)(const char*,const char*) = rename;
int(*p_renameat)(int,const char*,int,const char*) = renameat;
void(*p_rewind)(FILE*) = rewind;
int(*p_scanf)(const char*restrict,...) = scanf;
void(*p_setbuf)(FILE*restrict,char*restrict) = setbuf;
int(*p_setvbuf)(FILE*restrict,char*restrict,int,size_t) = setvbuf;
int(*p_snprintf)(char*restrict,size_t,const char*restrict,...) = snprintf;
int(*p_sprintf)(char*restrict,const char*restrict,...) = sprintf;
int(*p_sscanf)(const char*restrict,const char*restrict,...) = sscanf;
char*(*p_tempnam)(const char*,const char*) = tempnam;
FILE*(*p_tmpfile)(void) = tmpfile;
char*(*p_tmpnam)(char*) = tmpnam;
int(*p_ungetc)(int,FILE*) = ungetc;
}
#include <wchar.h>
static void g()
{
wint_t(*p_btowc)(int) = btowc;
wint_t(*p_fgetwc)(FILE*) = fgetwc;
wchar_t*(*p_fgetws)(wchar_t*restrict,int,FILE*restrict) = fgetws;
wint_t(*p_fputwc)(wchar_t,FILE*) = fputwc;
int(*p_fputws)(const wchar_t*restrict,FILE*restrict) = fputws;
int(*p_fwide)(FILE*,int) = fwide;
int(*p_fwprintf)(FILE*restrict,const wchar_t*restrict,...) = fwprintf;
int(*p_fwscanf)(FILE*restrict,const wchar_t*restrict,...) = fwscanf;
wint_t(*p_getwc)(FILE*) = getwc;
wint_t(*p_putwc)(wchar_t,FILE*) = putwc;
int(*p_swprintf)(wchar_t*restrict,size_t,const wchar_t*restrict,...) = swprintf;
int(*p_swscanf)(const wchar_t*restrict,const wchar_t*restrict,...) = swscanf;
wint_t(*p_ungetwc)(wint_t,FILE*) = ungetwc;
int(*p_wctob)(wint_t) = wctob;
int(*p_wprintf)(const wchar_t*restrict,...) = wprintf;
int(*p_wscanf)(const wchar_t*restrict,...) = wscanf;
}
#include <stdarg.h>
static void h()
{
int(*p_vdprintf)(int,const char*restrict,va_list) = vdprintf;
int(*p_vfprintf)(FILE*restrict,const char*restrict,va_list) = vfprintf;
int(*p_vfscanf)(FILE*restrict,const char*restrict,va_list) = vfscanf;
int(*p_vprintf)(const char*restrict,va_list) = vprintf;
int(*p_vscanf)(const char*restrict,va_list) = vscanf;
int(*p_vsnprintf)(char*restrict,size_t,const char*restrict,va_list) = vsnprintf;
int(*p_vsprintf)(char*restrict,const char*restrict,va_list) = vsprintf;
int(*p_vsscanf)(const char*restrict,const char*restrict,va_list) = vsscanf;

int(*p_vfwprintf)(FILE*restrict,const wchar_t*restrict,va_list) = vfwprintf;
int(*p_vfwscanf)(FILE*restrict,const wchar_t*restrict,va_list) = vfwscanf;
int(*p_vswprintf)(wchar_t*restrict,size_t,const wchar_t*restrict,va_list) = vswprintf;
int(*p_vswscanf)(const wchar_t*restrict,const wchar_t*restrict,va_list) = vswscanf;
int(*p_vwprintf)(const wchar_t*restrict,va_list) = vwprintf;
int(*p_vwscanf)(const wchar_t*restrict,va_list) = vwscanf;
}
