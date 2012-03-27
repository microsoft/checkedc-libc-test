DIRS = $(sort $(wildcard src/*))

all:
	for i in $(DIRS); do echo $$i; make -s -C $$i; done
t: all
#	for i in $(DIRS); do echo $$i; $$i/t; done
b: all
	for i in $(DIRS); do echo $$i; $$i/b; done
clean:
	for i in $(DIRS); do make -s -C $$i clean; done
