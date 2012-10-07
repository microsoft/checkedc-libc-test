include ../../Makefile.inc
LDFLAGS+=-lpthread

sem: LDFLAGS += -lrt
tls_align_dlopen: LDFLAGS += -ldl

tls_align: tls_align_dso.so

