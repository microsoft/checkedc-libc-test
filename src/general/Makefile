include ../../Makefile.inc

dlopen: LDFLAGS+=-ldl -rdynamic
pthread: LDFLAGS+=-lpthread
sem: LDFLAGS+=-lpthread -lrt
strtod_simple: LDFLAGS+=-lm
tls_align: tls_align_dso.so
tls_align_dlopen: LDFLAGS+=-ldl
