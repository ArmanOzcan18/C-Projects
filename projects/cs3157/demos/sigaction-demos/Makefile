CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

TARGETS = \
		sigint-ignore \
		sigint-handler \
		sigchld-handler \
		parenting

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

