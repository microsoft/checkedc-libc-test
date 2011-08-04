#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "test.h"

void *emptyfunc(void *dummy) {
	return 0;
}

void bench_pthread_createjoin_serial1(int N) {
	int i;
	pthread_t td;
	void *dummy;

	for (i=0; i<N; i++) {
		pthread_create(&td, 0, emptyfunc, 0);
		pthread_join(td, &dummy);
	}
}

void bench_pthread_createjoin_serial2(int N) {
	int i, j;
	pthread_t td[50];
	void *dummy;

	for (j=0; j<N/(sizeof td/sizeof *td); j++) {
		for (i=0; i<sizeof td/sizeof *td; i++)
			pthread_create(td+i, 0, emptyfunc, 0);
		for (i=0; i<sizeof td/sizeof *td; i++)
			pthread_join(td[i], &dummy);
	}
}

void bench_pthread_create_serial1(int N) {
	int i,j;
	pthread_attr_t attr;
	pthread_t td[50];
	void *dummy;

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 16384);
	for (j=0; j<N/(sizeof td/sizeof *td); j++) {
		for (i=0; i<sizeof td/sizeof *td; i++)
			pthread_create(td+i, &attr, emptyfunc, 0);
		stop_timer();
		for (i=0; i<sizeof td/sizeof *td; i++)
			pthread_join(td[i], &dummy);
		start_timer();
	}
}

static int lockN;
void *lockunlock(void *mut)
{
	int i;
	for (i=0; i<lockN; i++) {
		pthread_mutex_lock(mut);
		pthread_mutex_unlock(mut);
	}
	return 0;
}

void bench_pthread_uselesslock(int N) {
	pthread_t td;
	pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
	void *dummy;

	lockN = N;
	pthread_create(&td, 0, lockunlock, &mut);
	pthread_join(td, &dummy);
}

void bench_pthread_createjoin_min1(int N) {
	size_t i;
	pthread_t td;
	pthread_attr_t a;
	void *dummy;

	pthread_attr_init(&a);
	pthread_attr_setstacksize(&a, sysconf(_SC_PAGESIZE));
	pthread_attr_setguardsize(&a, 0);
	for (i=0; i<N; i++) {
		pthread_create(&td, &a, emptyfunc, 0);
		pthread_join(td, &dummy);
	}
}

void bench_pthread_createjoin_min2(int N) {
	int i, j;
	pthread_t td[50];
	pthread_attr_t a;
	void *dummy;

	pthread_attr_init(&a);
	pthread_attr_setstacksize(&a, sysconf(_SC_PAGESIZE));
	pthread_attr_setguardsize(&a, 0);
	for (j=0; j<N/(sizeof td/sizeof *td); j++) {
		for (i=0; i<sizeof td/sizeof *td; i++)
			pthread_create(td+i, &a, emptyfunc, 0);
		for (i=0; i<sizeof td/sizeof *td; i++)
			pthread_join(td[i], &dummy);
	}
}
