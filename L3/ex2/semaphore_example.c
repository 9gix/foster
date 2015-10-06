/*************************************
* Lab 3 Exercise 2
* Name:
* Student No:
* Lab Group:
*************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h> //For Semaphore. Use "-lrt" to compile

int main()
{
    int result, i;
    int shdMemIdForS;    
    sem_t* semPtr;

    //Create a shared memory region for Semaphore 
    shdMemIdForS = shmget( IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0666 );

    //Treat the shared memory region as a smepahore
    semPtr = (sem_t*) shmat(shdMemIdForS, NULL, 0);

    //Initializing the semaphore in shared memory region
    sem_init(semPtr, 1, 1);

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

        /*Important: Remember to detach the shared memory region*/
        shmdt( (char*)semPtr );

    } else {            //Child

        printf("%i is the child\n", (int)getpid());

        //TODO: Find out where to place the sem_wait() and sem_post()
        // to achieve the desired behavior

        for(i = 0; i < 3; i++){
            printf("c\n");
            sleep(1);
        }

        /*Important: Remember to detach the shared memory region*/
        shmdt( (char*)semPtr );
        return 0;   //Child Ends here

    }

    /*Important: Remember to remove the shared memory region after use!*/
    shmctl(shdMemIdForS, IPC_RMID, NULL); 
    return 0;
}
