#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

#define LEN 200000

static int bstrstr(int N, const char *needle) {
	size_t l = strlen(needle);
	size_t cnt = 10000;
	int i;
	int cs = 0;
	char *haystack = malloc(l * cnt + 1);

	for (i=0; i<cnt-1; i++) {
		memcpy(haystack + l*i, needle, l);
		haystack[l*i+l-1] ^= 1;
	}
	memcpy(haystack + l*i, needle, l+1);
	reset_timer();
	for (i=0; i<N; i++) {
		haystack[0]^=1;
		cs += (int)strstr(haystack, needle);
	}
	free(haystack);
	return cs;
}

void bench_string_strstr1(int N) {
	bstrstr(N, "abcdefghijklmnopqrstuvwxyz");
}
void bench_string_strstr2(int N) {
	bstrstr(N, "azbycxdwevfugthsirjqkplomn");
}
void bench_string_strstr3(int N) {
	bstrstr(N, "aaaaaaaaaaaaaacccccccccccc");
}
void bench_string_strstr4(int N) {
	bstrstr(N, "aaaaaaaaaaaaaaaaaaaaaaaaac");
}
void bench_string_strstr5(int N) {
	bstrstr(N, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaac");
}

void bench_string_memset(int N) {
	char *buf = malloc(LEN);
	int i;

	for (i=0; i<N; i++)
		memset(buf+i, i, LEN-i);
	free(buf);
}

void bench_string_strchr(int N) {
	char *buf = malloc(LEN);
	int i;
	int cs = 0;

	memset(buf, 'a', LEN);
	buf[LEN-1] = 0;
	buf[LEN-2] = 'b';
	reset_timer();
	for (i=0; i<N; i++) {
		buf[i] = '0'+i%8;
		cs ^= (int)strchr(buf, 'b');
	}
	buf[0] = cs;
	free(buf);
}

void bench_string_strlen(int N) {
	char *buf = malloc(LEN);
	int i;
	int cs = 0;

	memset(buf, 'a', LEN-1);
	buf[LEN-1] = 0;
	reset_timer();
	for (i=0; i<N; i++) {
		buf[i] = '0'+i%8;
		cs ^= strlen(buf);
	}
	buf[0] = cs;
	free(buf);
}
