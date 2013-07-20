$(N).LDLIBS := $(D)/tls_align_dso.so
$(N)-static.LDLIBS := $(D)/tls_align_dso.o

$(N): $(D)/tls_align_dso.so
$(N)-static: $(D)/tls_align_dso.o

