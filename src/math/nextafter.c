#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct dd_d t[] = {

};

int main(void)
{
	double y;
	float d;
	int e, i, err = 0;
	struct dd_d *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;
		setupfenv(p->r);
		y = nextafter(p->x, p->x2);
		e = getexcept();
		if (!checkexcept(e, p->e, p->r)) {
			printf("%s nextafter(%a,%a)==%a except: want %s", rstr(p->r), p->x, p->x2, p->y, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		d = ulperr(y, p->y, p->dy);
		if (!checkulp(d, p->r)) {
			printf("%s nextafter(%a,%a) want %a got %a ulperr %.3f = %a + %a\n",
				rstr(p->r), p->x, p->x2, p->y, y, d, d-p->dy, p->dy);
			err++;
		}
	}
	return !!err;
}
