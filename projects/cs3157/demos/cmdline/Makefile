CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

default: jsh-basic jsh jsh-io

jsh-basic: cmdline.o
jsh-basic.o: cmdline.h

jsh: cmdline.o
jsh.o: cmdline.h

jsh-io: cmdline.o
jsh-io.o: cmdline.h

cmdline.o: cmdline.h

.PHONY: clean
clean:
	rm -rf a.out *.o jsh-basic jsh jsh-io
