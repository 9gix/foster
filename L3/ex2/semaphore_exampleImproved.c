/*************************************
* Lab 3 Exercise 2 
* Name:
* Student No:
* Lab Group:
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

//A structure to store information useful for a semaphore
// semPtr = pointer to the actual sempahore structure sem_t
// shdMemId = the Id of the shared memory region used to allocate
//              the semaphore
typedef struct 
{
    sem_t* semPtr;
    int shdMemId;
} semInfoStruct;

//A function to allocate a shared memory region
// then place a sempahore in it
void newSemaphore( semInfoStruct* semInfo )
{
    //Create a shared memory region for Semaphore 
    semInfo->shdMemId = shmget( IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0666 );
   
    semInfo->semPtr = (sem_t*) shmat(semInfo->shdMemId, NULL, 0);
}

//Destroy the semaphore by detaching the shared memory region
void destroySempahore( semInfoStruct* semInfo )
{
    shmdt( (char*)semInfo->semPtr );
    shmctl( semInfo->shdMemId, IPC_RMID, NULL ); 
}

int main()
{
    int result, i;
    semInfoStruct mutex;

    newSemaphore(&mutex);

    sem_init(mutex.semPtr, 1, 1);

    result = fork();
    if (result){        //Parent
        printf("%i is the parent\n", (int)getpid());

        //TODO: Find out where to place the sem_wait() and sem_post()
        // to achieve the desired behavior

        for(i = 0; i < 3; i++){
            printf("p\n");
            sleep(1);
        }

        //wait for child to finish
        wait(&i);
        destroySempahore(&mutex);
    } else {            //Child

        printf("%i is the child\n", (int)getpid());

        //TODO: Find out where to place the sem_wait() and sem_post()
        // to achieve the desired behavior

        for(i = 0; i < 3; i++){
            printf("c\n");
            sleep(1);
        }

        destroySempahore(&mutex);
        return 0;   //Child Ends here

    }


    /*Important: Remember to remove the shared memory region after use!*/
    return 0;
}
