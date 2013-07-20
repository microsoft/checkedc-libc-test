$(N).BINS:=$(N)
$(N).LDFLAGS:=-rdynamic
$(N).err: $(D)/dlopen_dso.so
