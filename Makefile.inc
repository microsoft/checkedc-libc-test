# gnu makefile
# when included in src/*/Makefile then it builds a binary locally
# when included in ./Makefile then all tests are linked into one binary

ROOTDIR ?= ../..
ifeq ($(ROOTDIR), .)
SRCS = $(sort $(wildcard src/*/*.c))
else
SRCS = $(sort $(wildcard *.c))
endif
OBJS = $(SRCS:.c=.o)

usemusl = yes
prefix = /usr/local/musl
includedir = $(prefix)/include
libdir = $(prefix)/lib
-include $(ROOTDIR)/Makefile.conf


CFLAGS += -g -std=c99 -pipe -Wall
LDFLAGS += -g
INC += -I$(ROOTDIR)/common

ifeq ($(usemusl), yes)
CC=gcc
LIBCC=$(shell gcc -print-file-name=libgcc.a |sed 's,/libgcc.a,,')
#LIBCC=$(shell pcc -v /dev/null 2>&1 |sed -n 's,/crtbegin.o.*,,;s,.* /,/,p')
CFLAGS  += -nostdinc -ffreestanding -fno-stack-protector
LDFLAGS += -nostdlib -Wl,-e,_start,-Bstatic $(libdir)/crti.o $(libdir)/crt1.o $(libdir)/crtn.o -L $(libdir) -lc -L $(LIBCC) -l$(CC)
INC     += -isystem $(includedir)
endif

all: t

clean:
	rm -f $(OBJS) t main.o main.h

.c.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(OBJS): $(ROOTDIR)/common/test.h

main.h: $(OBJS)
	nm -f posix $+ |awk '/^test/ && $$2=="T"{print "T(" $$1 ")"}' >main.h

main.o: $(ROOTDIR)/common/main.c $(ROOTDIR)/common/test.h main.h
	$(CC) $(CFLAGS) $(INC) -I. -c -o $@ $<

t: $(OBJS) main.o
	$(CC) $+ $(LDFLAGS) -o $@

.PHONY: all clean
