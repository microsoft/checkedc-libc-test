#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include "test.h"

static void handler(int s)
{
}

static int start(char *argv[])
{
	int pid;

	pid = fork();
	if (pid == 0) {
		t_setrlim(RLIMIT_STACK, 100*1024);
		t_setrlim(RLIMIT_CPU, 2);
		execv(argv[0], argv);
		t_error("%s exec failed: %s\n", argv[0], strerror(errno));
		exit(1);
	}
	if (pid == -1) {
		t_error("%s fork failed: %s\n", argv[0], strerror(errno));
		exit(-1);
	}
	return pid;
}

int main(int argc, char *argv[])
{
	int status;
	sigset_t set;
	int timeout = 0;
	int sig = 0;
	int pid;

	if (argc < 2) {
		t_error("usage: ./runtest cmd [args..]\n");
		return -1;
	}
	argv++;
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, 0);
	signal(SIGCHLD, handler);
	pid = start(argv);
	if (sigtimedwait(&set, 0, &(struct timespec){5,0}) == -1) {
		if (errno == EAGAIN)
			timeout = 1;
		if (kill(pid, SIGKILL) == -1)
			t_error("%s kill failed: %s\n", argv[0], strerror(errno));
	}
	if (waitpid(pid, &status, 0) != pid) {
		t_error("%s waitpid failed: %s\n", argv[0], strerror(errno));
		return -1;
	}
	if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) == 0)
			return t_status;
		t_printf("FAIL %s [status %d]\n", argv[0], WEXITSTATUS(status));
	} else if (timeout) {
		t_printf("FAIL %s [timed out]\n", argv[0]);
	} else if (WIFSIGNALED(status)) {
		t_printf("FAIL %s [signal %s]\n", argv[0], strsignal(WTERMSIG(status)));
	} else
		t_printf("FAIL %s [unknown]\n", argv[0]);
	return 1;
}
