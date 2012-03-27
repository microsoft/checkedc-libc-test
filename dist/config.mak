# copy to ../config.mak and edit

# to test the native libc with native cc no config is required

# to test non-native musl with gcc use
#CC = musl-gcc

# to test non-native musl with installed pcc use
#prefix = /path/to/musl
#includedir = $(prefix)/include
#libdir = $(prefix)/lib
#CC = pcc
#LIBCC = $(shell pcc -v /dev/null 2>&1 |sed -n 's,/crtbegin.o.*,,;s,.* /,/,p')
#CFLAGS  += -nostdinc -ffreestanding -fno-stack-protector -isystem $(includedir)
#LDFLAGS += -nostdlib -Wl,-e,_start,-Bstatic $(libdir)/crti.o $(libdir)/crt1.o $(libdir)/crtn.o -L$(libdir) -lc -L$(LIBCC) -l$(CC)

# required for math tests
CFLAGS += -fno-builtin -ffloat-store
