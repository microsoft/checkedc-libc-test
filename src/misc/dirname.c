#define _GNU_SOURCE
#include "test.h"
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

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
