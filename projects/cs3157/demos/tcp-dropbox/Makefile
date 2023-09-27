CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

TARGETS = \
		tcp-dropbox-server \
		tcp-dropbox-server-sol \
		tcp-dropbox-client \

.PHONY: default
default: $(TARGETS)

# Executable for each target
$(TARGETS):

# Object file rules for each target
$(foreach t, $(TARGETS), $(t).o):

.PHONY: clean
clean:
	rm -rf *.o $(TARGETS)
