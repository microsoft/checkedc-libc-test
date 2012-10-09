#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct f_fi t[] = {
#include "sanity/lgammaf.h"

};

int main(void)
{
	int yi;
	double y;
	float d;
	int e, i, err = 0;
	struct f_fi *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;
		setupfenv(p->r);
		y = lgammaf(p->x);
		yi = signgam;
		e = getexcept();
		if (!checkexcept(e, p->e, p->r)) {
			printf("%s:%d: bad fp exception: %s lgammaf(%a)=%a,%lld, want %s",
				p->file, p->line, rstr(p->r), p->x, p->y, p->i, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		d = ulperrf(y, p->y, p->dy);
		if (!checkulp(d, p->r)) {
			printf("%s:%d: %s lgammaf(%a) want %a,%lld got %a,%d ulperr %.3f = %a + %a\n",
				p->file, p->line, rstr(p->r), p->x, p->y, p->i, y, yi, d, d-p->dy, p->dy);
			err++;
		}
	}
	return !!err;
}
