CFLAGS += -pipe -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wno-unused-function -Wno-missing-braces
CFLAGS += -Wno-unknown-pragmas -fno-builtin -frounding-math
CFLAGS += -g
LDFLAGS += -g
LDLIBS += -lpthread -lm -lrt

# glibc specific settings
CFLAGS += -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
LDLIBS += -lcrypt -ldl -lresolv -lutil

AR      = $(CROSS_COMPILE)ar
RANLIB  = $(CROSS_COMPILE)ranlib

