#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct l_l t[] = {
#if LDBL_MANT_DIG == 53
D
#include "sanity/tanl.h"
#elif LDBL_MANT_DIG == 64

#include "sanity/tanl.h"
#endif
};

int main(void)
{
	long double y;
	float d;
	int e, i, err = 0;
	struct l_l *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;
		setupfenv(p->r);
		y = tanl(p->x);
		e = getexcept();
		if (!checkexcept(e, p->e, p->r)) {
			printf("%s tanl(%La)==%La except: want %s", rstr(p->r), p->x, p->y, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		d = ulperrl(y, p->y, p->dy);
		if (!checkulp(d, p->r)) {
			printf("%s tanl(%La) want %La got %La ulperr %.3f = %a + %a\n",
				rstr(p->r), p->x, p->y, y, d, d-p->dy, p->dy);
			err++;
		}
	}
	return !!err;
}
