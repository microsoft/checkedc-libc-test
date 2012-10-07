DIRS = $(sort $(wildcard src/*))

all:
	for i in $(DIRS); do printf "%-20s" $$i; make -s -C $$i; done
run:
	for i in $(DIRS); do printf "%-20s" $$i; make -s -C $$i run; done
clean:
	for i in $(DIRS); do make -s -C $$i clean; done
