CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17

# These are all the executables to be built for this example
TARGETS = \
	stderr-is-unbuffered \
	stdout-fflushed \
	stdout-flushed-on-exit \
	stdout-flushed-on-fclose \
	stdout-is-buffered \
	stdout-not-flushed-on-crash \
	stdout-not-flushed-when-killed

# By default, build all of targets
.PHONY: default
default: $(TARGETS)

# Declare implicit rules for all targets
$(TARGETS):

# PHONY target to update .gitignore with all our targets
.PHONY: .gitignore
.gitignore:
	echo $(TARGETS) | tr ' ' '\n' > .gitignore
	echo '*.o' >> .gitignore

# Our good old friend, Mr Clean
.PHONY: clean
clean:
	rm -rf *.o a.out $(TARGETS)
