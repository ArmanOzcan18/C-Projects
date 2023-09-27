CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =
	
# convert depends on convert.o
convert: convert.o

# convert.o depends on convert.c
convert.o: convert.c

.PHONY: clean
clean:
	rm -f *.o a.out core convert

.PHONY: all
all: clean convert
