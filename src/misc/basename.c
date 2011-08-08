#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "test.h"

static void t(char *p, char *b) {
	char *tmp = strdup(p);
	char *s = basename(tmp);

	if (strcmp(b,s) != 0)
		error("basename(\"%s\") returned \"%s\"; expected \"%s\"\n", p, s, b);
	free(tmp);
}

void test_basename() {
	if (strcmp(".", basename(0)) != 0)
		error("basename(0) returned \"%s\"; expected \".\"\n", basename(0));
	t("", ".");
	t("/usr/lib", "lib");
	t("/usr/", "usr");
	t("/", "/");
	t("///", "/");
	t("//usr//lib//", "lib");
}
