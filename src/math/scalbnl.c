#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct li_l t[] = {
#if LDBL_MANT_DIG == 53
#include "sanity/scalbn.h"

#elif LDBL_MANT_DIG == 64
#include "sanity/scalbnl.h"

#endif
};

int main(void)
{
	long double y;
	float d;
	int e, i, err = 0;
	struct li_l *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;
		setupfenv(p->r);
		y = scalbnl(p->x, p->i);
		e = getexcept();
		if (!checkexcept(e, p->e, p->r)) {
			printf("%s:%d: bad fp exception: %s scalbnl(%La, %lld)=%La, want %s",
				p->file, p->line, rstr(p->r), p->x, p->i, p->y, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		d = ulperrl(y, p->y, p->dy);
		if (!checkulp(d, p->r)) {
			printf("%s:%d: %s scalbnl(%La, %lld) want %La got %La ulperr %.3f = %a + %a\n",
				p->file, p->line, rstr(p->r), p->x, p->i, p->y, y, d, d-p->dy, p->dy);
			err++;
		}
	}
	return !!err;
}
