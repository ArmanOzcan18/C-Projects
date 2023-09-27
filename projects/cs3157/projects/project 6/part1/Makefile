CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

.PHONY: default
default: http-server

http-server:

.PHONY: clean
clean:
	rm -rf a.out *.o http-server

.PHONY: all
all: clean http-server
