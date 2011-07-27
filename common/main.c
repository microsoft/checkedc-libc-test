#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "test.h"

#define T(t) void t();
#include "main.h"
#undef T

struct test test__ = {0};

static int verbose;
static int count;
static int nfailed;

static void run(const char *n, void (*f)()) {
	pid_t pid;
	int status;

	count++;
	test__.failed = 0;
	test__.name = n;
	if (verbose)
		fprintf(stderr, "running %s:\n", test__.name);

	pid = fork();
	if (pid == 0) {
		/* run test in a child process */
		f();
		exit(test__.failed);
	}

	if (pid == -1)
		error("fork failed: %s\n", strerror(errno));
	else {
		if (waitpid(pid, &status, 0) == -1)
			error("waitpid failed: %s\n", strerror(errno));
		else if (!WIFEXITED(status))
			error("abnormal exit: %s\n", WIFSIGNALED(status) ? strsignal(WTERMSIG(status)) : "(unknown)");
		else
			test__.failed = !!WEXITSTATUS(status);
	}

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
