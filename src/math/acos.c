#include "test.h"
#include <math.h>

void bench_acos(int N)
{
	int i;
	volatile double y;

	for (i = 0; i < N; i++) {
		y = acos(0.3456);
	}
}
