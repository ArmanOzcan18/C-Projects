
CC = gcc
CFLAGS = -g -Wall
LDFLAGS =

wordle: wordle-main.o words.o game.o
	$(CC) $(LDFLAGS) -o wordle wordle-main.o words.o game.o

wordle-main.o: wordle-main.c words.h
	$(CC) $(CFLAGS) -c -o wordle-main.o wordle-main.c

words.o: words.c words.h
	$(CC) $(CFLAGS) -c -o words.o words.c

game.o: game.c game.h words.h
	$(CC) $(CFLAGS) -c -o game.o game.c

.PHONY: test
test: wordle
	./run-tests.sh

.PHONY: clean
clean:
	rm -rf wordle a.out *.o test-output
