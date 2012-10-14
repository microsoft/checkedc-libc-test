#include <ctype.h>
#define T(t) (t*)0;
static void f()
{
int(*p_isalnum)(int) = isalnum;
int(*p_isalpha)(int) = isalpha;
int(*p_isascii)(int) = isascii;
int(*p_isblank)(int) = isblank;
int(*p_iscntrl)(int) = iscntrl;
int(*p_isdigit)(int) = isdigit;
int(*p_isgraph)(int) = isgraph;
int(*p_islower)(int) = islower;
int(*p_isprint)(int) = isprint;
int(*p_ispunct)(int) = ispunct;
int(*p_isspace)(int) = isspace;
int(*p_isupper)(int) = isupper;
int(*p_isxdigit)(int) = isxdigit;
int(*p_toascii)(int) = toascii;
int(*p_tolower)(int) = tolower;
int(*p_toupper)(int) = toupper;

#ifdef _POSIX_C_SOURCE
T(locale_t)
int(*p_isalnum_l)(int,locale_t) = isalnum_l;
int(*p_isalpha_l)(int,locale_t) = isalpha_l;
int(*p_isblank_l)(int,locale_t) = isblank_l;
int(*p_iscntrl_l)(int,locale_t) = iscntrl_l;
int(*p_isdigit_l)(int,locale_t) = isdigit_l;
int(*p_isgraph_l)(int,locale_t) = isgraph_l;
int(*p_islower_l)(int,locale_t) = islower_l;
int(*p_isprint_l)(int,locale_t) = isprint_l;
int(*p_ispunct_l)(int,locale_t) = ispunct_l;
int(*p_isspace_l)(int,locale_t) = isspace_l;
int(*p_isupper_l)(int,locale_t) = isupper_l;
int(*p_isxdigit_l)(int,locale_t) = isxdigit_l;
int(*p_tolower_l)(int,locale_t) = tolower_l;
int(*p_toupper_l)(int,locale_t) = toupper_l;
#endif

#ifdef _XOPEN_SOURCE
int(*p__tolower)(int) = _tolower;
int(*p__toupper)(int) = _toupper;
#endif
}
