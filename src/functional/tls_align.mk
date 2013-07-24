$(N).LDLIBS := $(B)/$(D)/tls_align_dso.so
$(N)-static.LDLIBS := $(B)/$(D)/tls_align_dso.o

$(B)/$(N): $(B)/$(D)/tls_align_dso.so
$(B)/$(N)-static: $(B)/$(D)/tls_align_dso.o

