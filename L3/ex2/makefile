all:	ex2 semaphore semaphoreImproved

ex2:	ex2.c
	gcc -Wall ex2.c -pthread -o ex2

semaphore: semaphore_example.c
	gcc -Wall semaphore_example.c -pthread -o semaphore

semaphoreImproved: semaphore_exampleImproved.c
	gcc -Wall semaphore_exampleImproved.c -pthread -o semaphoreImproved

clean:
	rm -f ex2 semaphore semaphoreImproved
