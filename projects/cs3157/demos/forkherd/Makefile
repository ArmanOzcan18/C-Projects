CC = gcc
CFLAGS = -Wall

forkherd:

# Run the test according to the questions, producing a timeline of events.
.PHONY: run
run: forkherd
	./runtest.sh

# Run the test, and sort answers by question (instead of chronologically).
.PHONY: answer
answer: forkherd
	./runtest.sh | grep -vE '^#' | grep . | sort

.PHONY:
clean:
	rm -ff *.o a.out A.* B.* forkherd
