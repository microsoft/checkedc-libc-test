DIRS = $(sort $(wildcard src/*))

all:
	for i in $(DIRS); do printf "%-20s" $$i; make -s -C $$i; done
t:
	@for i in $(DIRS); do printf "%-20s" $$i; make -s -C $$i 2>/dev/null; done
b: t
	@for i in $(DIRS); do echo $$i; $$i/b; done
clean:
	for i in $(DIRS); do make -s -C $$i clean; done
