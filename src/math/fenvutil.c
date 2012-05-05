#include <fenv.h>
#include <stdio.h>
#include "fenvutil.h"

static struct {
	int flag;
	char *s;
} eflags[] = {
	{FE_INVALID, "FE_INVALID"},
	{FE_DIVBYZERO, "FE_DIVBYZERO"},
	{FE_OVERFLOW, "FE_OVERFLOW"},
	{FE_UNDERFLOW, "FE_UNDERFLOW"},
	{FE_INEXACT, "FE_INEXACT"},
};
static int ne = sizeof eflags / sizeof *eflags;

static struct {
	int flag;
	char *s;
} rflags[] = {
	{FE_TONEAREST,"FE_TONEAREST"},
	{FE_DOWNWARD,"FE_DOWNWARD"},
	{FE_UPWARD,"FE_UPWARD"},
	{FE_TOWARDZERO,"FE_TOWARDZERO"},
};
static int nr = sizeof rflags / sizeof *rflags;

char *strexcept(int f) {
	static char buf[256];
	char *p;
	int i, all=0;

	p = buf;
	for (i = 0; i < ne; i++)
		if (f & eflags[i].flag) {
			p += sprintf(p, "%s%s", all ? "|" : "", eflags[i].s);
			all |= eflags[i].flag;
		}
	if (all != f) {
		p += sprintf(p, "%s%d", all ? "|" : "", f & ~all);
		all = f;
	}
	p += sprintf(p, "%s", all ? "" : "0");
	return buf;
}

char *strround(int f) {
	static char buf[256];
	int i;

	for (i = 0; i < nr; i++)
		if (f == rflags[i].flag) {
			sprintf(buf, "%s", rflags[i].s);
			return buf;
		}
	sprintf(buf, "%d", f);
	return buf;
}

