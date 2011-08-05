#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <locale.h>
#include "test.h"


void bench_regex_compile(int N) {
	regex_t re;
	int i;

	setlocale(LC_CTYPE, "");
	for (i=0; i<N; i++) {
		regcomp(&re, "(a|b|c)*d*b", REG_EXTENDED);
		regfree(&re);
	}
}

static void regex_search(int N, char *s) {
	char buf[100000];
	regex_t re;
	int i;

	setlocale(LC_CTYPE, "");
	memset(buf, 'a', sizeof(buf)-2);
	buf[sizeof buf - 2] = 'b';
	buf[sizeof buf - 1] = 0;
	regcomp(&re, s, REG_EXTENDED);
	for (i=0; i<N; i++)
		regexec(&re, buf, 0, 0, 0);
	regfree(&re);
}

void bench_regex_search1(int N) {
	regex_search(N, "(a|b|c)*d*b");
}

void bench_regex_search2(int N) {
	regex_search(N, "a{25}b");
}
