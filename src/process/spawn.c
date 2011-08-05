#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <spawn.h>
#include <sys/wait.h>
#include "test.h"

#define TEST(r, f, x, m) ( \
	((r) = (f)) == (x) || \
	(error("%s failed (" m ")\n", #f, r, x), 0) )

#define TEST_E(f) ( (errno = 0), (f) || \
	(error("%s failed (errno = %d \"%s\")\n", #f, errno, strerror(errno)), 0) )

void test_spawn(void) {
	int r;
	char foo[10];
	int p[2];
	pid_t pid;
	int status;
	posix_spawnattr_t attr;
	posix_spawn_file_actions_t fa;

	TEST_E(!pipe(p));
	TEST(r, posix_spawn_file_actions_init(&fa), 0, "%d != %d");
	TEST(r, posix_spawn_file_actions_addclose(&fa, p[0]), 0, "%d != %d");
	TEST(r, posix_spawn_file_actions_adddup2(&fa, p[1], 1), 0, "%d != %d");
	TEST(r, posix_spawn_file_actions_addclose(&fa, p[1]), 0, "%d != %d");
	TEST(r, posix_spawnp(&pid, "echo", &fa, 0, (char *[]){"echo","hello",0}, 0), 0, "%d != %d");
	close(p[1]);
	TEST(r, waitpid(pid, &status, 0), pid, "%d != %d");
	TEST(r, read(p[0], foo, sizeof foo), 6, "%d != %d");
	close(p[0]);
	TEST(r, posix_spawn_file_actions_destroy(&fa), 0, "%d != %d");
}
