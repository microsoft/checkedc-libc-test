#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "test.h"

static int scmp(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

static int icmp(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

/* 26 items -- even */
static char *s[] = {
	"Bob", "Alice", "John", "Ceres",
	"Helga", "Drepper", "Emeralda", "Zoran",
	"Momo", "Frank", "Pema", "Xavier",
	"Yeva", "Gedun", "Irina", "Nono",
	"Wiener", "Vincent", "Tsering", "Karnica",
	"Lulu", "Quincy", "Osama", "Riley",
	"Ursula", "Sam"
};
/* 23 items -- odd, prime */
static int n[] = {
	879045, 394, 99405644, 33434, 232323, 4334, 5454,
	343, 45545, 454, 324, 22, 34344, 233, 45345, 343,
	848405, 3434, 3434344, 3535, 93994, 2230404, 4334
};

void test_qsort(void) {
	int i;

	qsort(s, sizeof(s)/sizeof(char *), sizeof(char *), scmp);
	for (i=0; i<sizeof(s)/sizeof(char *)-1; i++) {
		if (strcmp(s[i], s[i+1]) > 0) {
			error("string sort failed at index %d\n", i);
			for (i=0; i<sizeof(s)/sizeof(char *); i++)
				fprintf(stderr, "\t%d\t%s\n", i, s[i]);
			break;
		}
	}

	qsort(n, sizeof(n)/sizeof(int), sizeof(int), icmp);
	for (i=0; i<sizeof(n)/sizeof(int)-1; i++) {
		if (n[i] > n[i+1]) {
			error("integer sort failed at index %d\n", i);
			for (i=0; i<sizeof(n)/sizeof(int); i++)
				fprintf(stderr, "\t%d\t%d\n", i, n[i]);
			break;
		}
	}
}

void bench_qsort_small(int N) {
	int i;
	int *a = malloc(sizeof n);

	for (i = 0; i < N; i++) {
		memcpy(a, n, sizeof n);
		qsort(a, sizeof n/sizeof *n, sizeof *a, icmp);
	}
	free(a);
}

void bench_qsort_large(int N) {
	int i,j;
	int len = 10000;
	int *a = malloc(len * sizeof *a);

	for (i = 0; i < N; i++) {
		srand(13);
		for (j = 0; j < len; j++)
			a[j] = rand();
		qsort(a, len, sizeof *a, icmp);
	}
	free(a);
}
