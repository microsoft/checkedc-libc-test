#include <wctype.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(wint_t)
T(wctrans_t)
T(wctype_t)
#ifdef _POSIX_C_SOURCE
T(locale_t)
#endif
C(WEOF)
int(*p_iswalnum)(wint_t) = iswalnum;
int(*p_iswalpha)(wint_t) = iswalpha;
int(*p_iswblank)(wint_t) = iswblank;
int(*p_iswcntrl)(wint_t) = iswcntrl;
int(*p_iswctype)(wint_t,wctype_t) = iswctype;
int(*p_iswdigit)(wint_t) = iswdigit;
int(*p_iswgraph)(wint_t) = iswgraph;
int(*p_iswlower)(wint_t) = iswlower;
int(*p_iswprint)(wint_t) = iswprint;
int(*p_iswpunct)(wint_t) = iswpunct;
int(*p_iswspace)(wint_t) = iswspace;
int(*p_iswupper)(wint_t) = iswupper;
int(*p_iswxdigit)(wint_t) = iswxdigit;
wint_t(*p_towctrans)(wint_t,wctrans_t) = towctrans;
wint_t(*p_towlower)(wint_t) = towlower;
wint_t(*p_towupper)(wint_t) = towupper;
wctrans_t(*p_wctrans)(const char*) = wctrans;
wctype_t(*p_wctype)(const char*) = wctype;
#ifdef _POSIX_C_SOURCE
int(*p_iswalnum_l)(wint_t,locale_t) = iswalnum_l;
int(*p_iswalpha_l)(wint_t,locale_t) = iswalpha_l;
int(*p_iswblank_l)(wint_t,locale_t) = iswblank_l;
int(*p_iswcntrl_l)(wint_t,locale_t) = iswcntrl_l;
int(*p_iswctype_l)(wint_t,wctype_t,locale_t) = iswctype_l;
int(*p_iswdigit_l)(wint_t,locale_t) = iswdigit_l;
int(*p_iswgraph_l)(wint_t,locale_t) = iswgraph_l;
int(*p_iswlower_l)(wint_t,locale_t) = iswlower_l;
int(*p_iswprint_l)(wint_t,locale_t) = iswprint_l;
int(*p_iswpunct_l)(wint_t,locale_t) = iswpunct_l;
int(*p_iswspace_l)(wint_t,locale_t) = iswspace_l;
int(*p_iswupper_l)(wint_t,locale_t) = iswupper_l;
int(*p_iswxdigit_l)(wint_t,locale_t) = iswxdigit_l;
wint_t(*p_towctrans_l)(wint_t,wctrans_t,locale_t) = towctrans_l;
wint_t(*p_towlower_l)(wint_t,locale_t) = towlower_l;
wint_t(*p_towupper_l)(wint_t,locale_t) = towupper_l;
wctrans_t(*p_wctrans_l)(const char*,locale_t) = wctrans_l;
wctype_t(*p_wctype_l)(const char*,locale_t) = wctype_l;
#endif
}
