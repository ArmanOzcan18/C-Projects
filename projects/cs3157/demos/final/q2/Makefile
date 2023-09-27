CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

FGTESTS = \
		fgtest \
		fgtest1 \
		fgtest2 \
		fgtest3 \
		fgtest4 \
		fgtest5 \
		fgtest6

.PHONY: default clean all
default:
	@echo "This Makefile is useless other than for 'make clean'"
	@echo
	@echo "If you want to run this problem, execute './test-all.sh'"

clean:
	rm -rf a.out *.o $(FGTESTS)

all: clean
