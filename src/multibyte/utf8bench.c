#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <langinfo.h>

#define LEN 500000

static char *initbuf() {
	char *buf;
	int i, j, k, l;

	setlocale(LC_CTYPE, "C.UTF-8")
	|| setlocale(LC_CTYPE, "en_US.UTF-8")
	|| setlocale(LC_CTYPE, "en_GB.UTF-8")
	|| setlocale(LC_CTYPE, "en.UTF-8")
	|| setlocale(LC_CTYPE, "de_DE-8")
	|| setlocale(LC_CTYPE, "fr_FR-8");
	if (strcmp(nl_langinfo(CODESET), "UTF-8")) exit(1);

	buf = malloc(LEN);
	l = 0;
	for (i=0xc3; i<0xe0; i++)
		for (j=0x80; j<0xc0; j++)
			buf[l++] = i, buf[l++] = j;
	for (i=0xe1; i<0xed; i++)
		for (j=0x80; j<0xc0; j++)
			for (k=0x80; k<0xc0; k++)
				buf[l++] = i, buf[l++] = j, buf[l++] = k;
	for (i=0xf1; i<0xf4; i++)
		for (j=0x80; j<0xc0; j++)
			for (k=0x80; k<0xc0; k++)
				buf[l++] = i, buf[l++] = j, buf[l++] = 0x80, buf[l++] = k;
	buf[l++] = 0;
	return buf;
}

void bench_utf8_bigbuf(int N) {
	char *buf;
	wchar_t *wbuf;
	int i;
	int cs;

	buf = initbuf();
	wbuf = malloc(LEN*sizeof(wchar_t));
	for (i=0; i<N; i++)
		cs ^= mbstowcs(wbuf, buf, LEN);
	buf[0] = cs;
	free(wbuf);
	free(buf);
}

void bench_utf8_onebyone(int N) {
	char *buf;
	wchar_t wc;
	int i, j;
	mbstate_t st = {0};

	buf = initbuf();
	for (i=0; i<N; i++) {
		for (j=0; buf[j]; j+=mbrtowc(&wc, buf+j, 4, &st));
	}
	free(buf);
}
