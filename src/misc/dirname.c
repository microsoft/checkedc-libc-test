#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "test.h"

static void t(char *p, char *b) {
	char *tmp = strdup(p);
	char *s = dirname(tmp);

	if (strcmp(b,s) != 0)
		error("dirname(\"%s\") returned \"%s\"; expected \"%s\"\n", p, s, b);
	free(tmp);
}

void test_dirname() {
	if (strcmp(dirname(0), ".") != 0)
		error("dirname(0) returned \"%s\"; expected \".\"\n", dirname(0));
	t("", ".");
	t("/usr/lib", "/usr");
	t("/usr/", "/");
	t("usr", ".");
	t("/", "/");
	t("///", "/");
	t(".", ".");
	t("..", ".");
}
