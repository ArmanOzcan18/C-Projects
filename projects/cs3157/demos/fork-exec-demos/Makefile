CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

TARGETS = \
		fork-hello \
		fork-negotiate \
		fork-wait \
		fork-wait-many \
		exec-test \
		fork-exec-echo \
		fork-exec-ls \
		fork-exec-myprogram \
		myprogram

.PHONY: default
default: $(TARGETS)

$(TARGETS):
$(foreach target,$(TARGETS),$(target).o):

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.o a.out

.PHONY: all
all: clean default

.PHONY: .gitignore
.gitignore:
	echo '*.o' > .gitignore
	echo 'a.out' >> .gitignore
	echo "$(TARGETS)" | tr ' ' '\n' >> .gitignore

