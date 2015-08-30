CC=gcc
CFLAGS=-c

.PHONY: clean

all: clean ex2

ex1: ex2.o
	$(CC) ex2.o -o ex1

ex1.o: ex2.c
	$(CC) $(CFLAGS) ex2.c

clean:
	-@rm -rf *.o ex2 2>/dev/null || true
