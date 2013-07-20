#include <unistd.h>
#include "test.h"

void t_fdfill(void)
{
	int fd[2];
	while (pipe(fd) == 0);
	dup(0);
}
