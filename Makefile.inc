# gnu makefile
# when included in a Makefile it builds *.c unless SRCS are overridden

# default TROOT works from src/*/Makefile
TROOT ?= ../..
SRCS ?= $(sort $(wildcard *.c))
OBJS = $(SRCS:.c=.o)

AR=ar
RANLIB=ranlib

CFLAGS += -g -D_POSIX_C_SOURCE=200809L -std=c99 -pipe -Wall
LDFLAGS += -g -lpthread -lrt -lm

-include $(TROOT)/config.mak

CFLAGS += -I$(TROOT)/common

all: test

test: t b
	./t

clean:
	rm -f $(OBJS) t t_.o b b_.o tests.a tests.h

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJS): $(TROOT)/common/test.h

tests.h: $(OBJS)
	nm -f posix $+ |awk ' \
		/^test/ && $$2=="T"{print "T(" $$1 ")"} \
		/^bench/ && $$2=="T"{print "B(" $$1 ")"} \
	' >tests.h

tests.a: $(OBJS)
	$(AR) rc $@ $+
	$(RANLIB) $@

# TODO: /tmp/t.o ?
t_.o: $(TROOT)/common/t.c $(TROOT)/common/test.h tests.h
	$(CC) $(CFLAGS) -I. -c -o $@ $<

t: t_.o tests.a
	$(CC) $+ $(LDFLAGS) -o $@

b_.o: $(TROOT)/common/b.c $(TROOT)/common/test.h tests.h
	$(CC) $(CFLAGS) -I. -c -o $@ $<

b: b_.o tests.a
	$(CC) $+ $(LDFLAGS) -lrt -o $@

.PHONY: all clean test
