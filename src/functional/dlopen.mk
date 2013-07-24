$(N).BINS:=$(B)/$(N)
$(N).LDFLAGS:=-rdynamic
$(B)/$(N).err: $(B)/$(D)/dlopen_dso.so
