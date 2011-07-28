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
static unsigned long long ns;
//static unsigned long long bytes;

#define SEC  1000000000ULL
#define MAXN 1000000000

static unsigned long long nsclock() {
	struct timespec ts;
	int r;

#ifdef _POSIX_CPUTIME
	r = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
#else
#ifdef _POSIX_MONOTONIC_CLOCK
	r = clock_gettime(CLOCK_MONOTONIC, &ts);
#else
	r = clock_gettime(CLOCK_REALTIME, &ts);
#endif
#endif
	if (r < 0) {
		fprintf(stderr, "bench: clock_gettime failed: %s\n", strerror(errno));
		return 0;
	}
	return ts.tv_sec*SEC + ts.tv_nsec;
}

void start_timer() {
	if (!start)
		start = nsclock();
}

void stop_timer() {
	if (start)
		ns += nsclock() - start;
	start = 0;
}

void reset_timer() {
	if (start)
		start = nsclock();
	ns = 0;
}

static int nextN() {
	unsigned long long n = ns/N;
	if (n == 0)
		n = SEC;
	else
		n = SEC/n;
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
		if (ns > SEC || N >= MAXN)
			break;
		if (N <= 0) {
			fprintf(stderr, "bench: fatal: N <= 0\n");
			return;
		}
	}
	if (ns/N > 100)
		fprintf(stderr, "%10d%10llu ns/op\n", N, ns/N);
	else
		fprintf(stderr, "%10d%13.2f ns/op\n", N, (double)ns/N);
}

int main() {
#define B(t) run(#t, t);
#include "main.h"
	return 0;
}
