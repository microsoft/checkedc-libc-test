#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "test.h"

#define T(f)
#define B(f) void f(int);
#include "tests.h"
#undef B

static int verbose = 1;

void error__(const char *n, int l, const char *s, ...) {
	fprintf(stderr, "use error in tests only\n");
}

static int N;
static unsigned long long start;
static unsigned long long dt;
//static unsigned long long bytes;

#define SEC  1000000000ULL
#define MAXN  500000000

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
	unsigned long long i;

	if (n)
		n = SEC/2/n;
	else
		n = SEC/2;
	n += n/2;
	if (n > N*100ULL)
		n = N*100ULL;
	else if (n <= N)
		n = N+1;
	if (n > MAXN)
		n = MAXN;

	/* round up to a nice number */
	for (i = 1; i < n; i *= 10);
	if (i/2 >= n)
		i /= 2;
	if (i/2 >= n)
		i /= 2;
	return i;
}

void vmstats() {
	FILE *f;
	char buf[256];
	int maj, min, in_heap=0;
	unsigned long l;
	size_t vm_size=0, vm_rss=0, vm_priv_dirty=0;

	f = fopen("/proc/self/smaps", "rb");
	if (f) while (fgets(buf, sizeof buf, f)) {
		if (sscanf(buf, "%*lx-%*lx %*s %*lx %x:%x %*lu %*s", &maj, &min)==2)
			in_heap = (!maj && !min && !strstr(buf, "---p") && (strstr(buf, "[heap]") || !strchr(buf, '[')));
		if (in_heap) {
			if (sscanf(buf, "Size: %lu", &l)==1) vm_size += l;
			else if (sscanf(buf, "Rss: %lu", &l)==1) vm_rss += l;
			else if (sscanf(buf, "Private_Dirty: %lu", &l)==1) vm_priv_dirty += l;
		}
	}
	if (f) fclose(f);
	fprintf(stderr, " %7zu virt %7zu res %7zu dirty", vm_size, vm_rss, vm_priv_dirty);
}

void stats() {
	if (dt/N > 100)
		fprintf(stderr, "%10d N %10llu ns/op   ", N, dt/N);
	else
		fprintf(stderr, "%10d N %13.2f ns/op", N, (double)dt/N);
	if (verbose)
		vmstats();
	fputc('\n', stderr);
}

static void run(const char *name, void (*f)(int)) {
	int p = fork();
	if (p) {
		int s;
		if (p<0 || wait(&s)<0 || !WIFEXITED(s) || WEXITSTATUS(s))
			fprintf(stderr, "benchmark %s failed\n", name);
		return;
	}
	fprintf(stderr, "%-32s", name);
	for (N=1; ; N=nextN()) {
		// TODO: fork at each iteration and pass N,dt..?
		reset_timer();
		start_timer();
		f(N);
		stop_timer();
//		fprintf(stderr, "%10d%12llu next: %d\n", N, dt, nextN());
		if (dt >= SEC/2 || N >= MAXN) {
			stats();
			exit(0);
		}
		if (N <= 0) {
			fprintf(stderr, "bench: fatal: N <= 0\n");
			exit(1);
		}
	}
}

int main() {
#define B(t) run(#t, t);
#include "tests.h"
	return 0;
}
