CC=gcc
CFLAGS=

.PHONY: clean

all: clean ex3

ex3: ex3.c
	$(CC) $(CFLAGS) ex3.c -o ex3

clean:
	-@rm -rf *.o ex1 2>/dev/null || true
