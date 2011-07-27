#include "test.h"

#define T(t) void t();
#include "main.h"
#undef T

struct test test__ = {0};

static int verbose;
static int count;
static int nfailed;

static void run(const char *n, void (*f)()) {
	count++;
	test__.failed = 0;
	test__.name = n;
	if (verbose)
		fprintf(stderr, "running %s:\n", test__.name);
	f();
	if (test__.failed) {
		nfailed++;
		fprintf(stderr, "FAILED %s\n", test__.name);
	} else if (verbose)
		fprintf(stderr, "PASSED %s\n", test__.name);
}

static int summary() {
	fprintf(stderr, "PASS:%d FAIL:%d\n", count-nfailed, nfailed);
	return !!nfailed;
}

int main() {
#define T(t) run(#t, t);
#include "main.h"
	return summary();
}
