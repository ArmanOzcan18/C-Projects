CC = gcc
CFLAGS ?= -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

gtg: fast.o
gtg.o: fast.h
fast.o: fast.h

.PHONY: clean all
clean:
	rm -rf *.o gtg
all: clean gtg
