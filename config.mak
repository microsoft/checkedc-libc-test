CC=clang
CFLAGS += -pipe -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wno-unused-function -Wno-missing-braces -Wno-unused -Wno-overflow
CFLAGS += -Wno-unknown-pragmas -fno-builtin
CFLAGS += -Werror=implicit-function-declaration -Werror=implicit-int -Werror=pointer-sign -Werror=pointer-arith
CFLAGS += -g
LDFLAGS += -g
LDLIBS += -Wl,--start-group -lpthread -lm -lrt -lc -lclang_rt.builtins-x86_64 -Wl,--end-group

MUSL_CFLAGS=-nostdinc -isystem $(MUSL_PATH)/include
MUSL_LDFLAGS=-nostdlib -L $(MUSL_PATH)/lib -L $(RT_PATH)/lib/clang/10.0.0/lib/linux $(MUSL_PATH)/lib/libc.a $(MUSL_PATH)/lib/crt1.o $(MUSL_PATH)/lib/crti.o $(MUSL_PATH)/lib/crtn.o

CFLAGS += $(MUSL_CFLAGS) -fPIC -Wno-switch-bool -Wno-empty-translation-unit
LDFLAGS += $(MUSL_LDFLAGS) -fPIC

# glibc specific settings
CFLAGS += -D_FILE_OFFSET_BITS=64
LDLIBS += -lcrypt -ldl -lresolv -lutil -lpthread

