TROOT=.
include Makefile.inc


# build binary in each test dir
DIRS = $(sort $(wildcard src/*))

local:
	for i in $(DIRS); do make -C $$i; done
localrun: local
	for i in $(DIRS); do $$i/t; done
localclean:
	for i in $(DIRS); do make -C $$i clean; done
cleanall: clean localclean
