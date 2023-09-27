CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

TARGETS = \
		exec-demo \
		fork-numbers1 \
		fork-numbers2 \
		fork-numbers3 \
		fffork \
		eeexec


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

