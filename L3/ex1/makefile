all:	shdMem server client ex1

ex1:	ex1.c
	gcc -Wall ex1.c -o ex1

shdMem:	shdMemAndFork.c
	gcc -Wall shdMemAndFork.c -o shdMem

server:	server.c
	gcc -Wall server.c -o server

client:	client.c
	gcc -Wall client.c -o client

clean:
	rm -f shdMem server client ex1
