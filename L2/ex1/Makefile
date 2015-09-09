CC=gcc
CFLAGS=-c

.PHONY: clean

all: clean ex1

ex1: ex1.o
	$(CC) ex1.o -o ex1

ex1.o: ex1.c
	$(CC) $(CFLAGS) ex1.c

clean:
	-@rm -rf *.o ex1 2>/dev/null || true
