#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "test.h"

#define T(t)
#define B(t) void t();
#include "main.h"
#undef B

//static int verbose;

void error__(const char *n, int l, const char *s, ...) {
	fprintf(stderr, "use error in tests only\n");
}

int N;
static unsigned long long start;
static unsigned long long dt;
//static unsigned long long bytes;

#define SEC  1000000000ULL
#define MAXN 1000000000

static unsigned long long tic() {
	struct timespec ts;

	if (clock_gettime(CLOCK_MONOTONIC, &ts) < 0) {
		fprintf(stderr, "bench: clock_gettime failed: %s\n", strerror(errno));
		return 0;
	}
	return ts.tv_sec*SEC + ts.tv_nsec;
}

void start_timer() {
	if (!start)
		start = tic();
}

void stop_timer() {
	if (start)
		dt += tic() - start;
	start = 0;
}

void reset_timer() {
	if (start)
		start = tic();
	dt = 0;
}

static int nextN() {
	unsigned long long n = dt/N;

	if (n)
		n = SEC/n;
	else
		n = SEC;
	n += n/4;
	if (n > N*100ULL)
		n = N*100ULL;
	else if (n <= N)
		n = N+1;
	if (n > MAXN)
		n = MAXN;
	return n;
}

static void run(const char *name, void (*f)()) {
	fprintf(stderr, "%s:", name);
	for (N=1; ; N=nextN()) {
		reset_timer();
		start_timer();
		f();
		stop_timer();
//		fprintf(stderr, "%10d%12llu\n", N, ns);
		if (dt >= SEC || N >= MAXN)
			break;
		if (N <= 0) {
			fprintf(stderr, "bench: fatal: N <= 0\n");
			return;
		}
	}
	if (dt/N > 100)
		fprintf(stderr, "%10d%10llu ns/op\n", N, dt/N);
	else
		fprintf(stderr, "%10d%13.2f ns/op\n", N, (double)dt/N);
}

int main() {
#define B(t) run(#t, t);
#include "main.h"
	return 0;
}
