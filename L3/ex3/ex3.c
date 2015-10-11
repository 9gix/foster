/*************************************
* Lab 3 Exercise 3
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

#define BUFFERSIZE 100

typedef struct 
{
    sem_t* semPtr;
    int shdMemId;
} semInfoStruct;

void newSemaphore( semInfoStruct* semInfo )
{
    //Create a shared memory region for Semaphore 
    semInfo->shdMemId = shmget( IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0666 );
   
    semInfo->semPtr = (sem_t*) shmat(semInfo->shdMemId, NULL, 0);
}

void destroySempahore( semInfoStruct* semInfo )
{
    shmdt( (char*)semInfo->semPtr );
    shmctl(semInfo->shdMemId, IPC_RMID, NULL); 
}

void Producer(int id, int* countLoc, int* index, int* auditArea, int* bufferArea,
        semInfoStruct* mutex, semInfoStruct* fillCount, semInfoStruct* emptyCount)
{
    int stop = 0;

    //Some simple code are written for you. You are free to rewrite in
    //anyway
    
    printf("Producer %i Starts to work!\n", id);
    while(!stop){



        if (*index == BUFFERSIZE) {
            *index = 0;
        }

        sem_wait(emptyCount->semPtr);
        sem_wait(mutex->semPtr);
        bufferArea[*index] = id;
        auditArea[id] += 1;
        *index += 1;
        *countLoc -= 1;

        sem_post(mutex->semPtr);
        sem_post(fillCount->semPtr);

        if (*countLoc == 0)
            stop = 1;
    }
    printf("Producer %i Ended!\n", id);

}

void Consumer(int id, int* countLoc, int* index, int* auditArea, int* bufferArea,
        semInfoStruct* mutex, semInfoStruct* fillCount, semInfoStruct* emptyCount)
{
    int stop = 0;

    //Some simple code are written for you. You are free to rewrite in
    //anyway


    printf("Consumer %i Starts to work!\n", id);
    while(!stop){

        //TODO:Fill in your code here
        if (*index == BUFFERSIZE) {
            *index = 0;
        }

        sem_wait(fillCount->semPtr);
        sem_wait(mutex->semPtr);
        auditArea[id] += 1; //bufferArea[*index];
        *index += 1;
        *countLoc -= 1;
        sem_post(mutex->semPtr);
        sem_post(emptyCount->semPtr);

        if (*countLoc == 0)
            stop = 1;
    }

    //Hint: Other consumers may still be waiting
    //      Find a simple way to release them.....
    printf("Consumer %i Ended!\n", id);
}


int main(int argc, char** argv)
{
    int shdMemId, result, i;
    int shdMemSize; 
    int *sharedArray;
    int nProducer, nConsumer, totalChild, M;

    //Checking and converting cmd line arguments
    //No need to change
    if (argc < 4){
        printf("Usage: a.out nProducers nConsumers totalProductionCount\n");
        exit(1);
    }
    nProducer = atoi(argv[1]);
    nConsumer = atoi(argv[2]);
    M = atoi(argv[3]);
    totalChild = nProducer+nConsumer;

    printf("Running with %i Producer(s) and %i Consumer(s).",
        nProducer, nConsumer);

    printf("Total Production Count = %i\n", M);


     //Create a new shared memory region
    shdMemSize = sizeof(int) * (2*nProducer + 4 + BUFFERSIZE);
 
    shdMemId = shmget( IPC_PRIVATE, shdMemSize, IPC_CREAT | 0666 );
    if (shdMemId < 0){
        printf("Cannot create shared memory region!\n");
        exit(1);
    }
    printf("Shared Memory Id is %i\n",shdMemId);

    //Attach a new shared memory region
    sharedArray = (int*) shmat(shdMemId, NULL, 0);
    if ( sharedArray == (int*)-1){
        printf("Cannot attach shared memory region!\n");
        exit(1);
    }

    //Initialize Audit and Bookkeeping info
    sharedArray[0] = M;
    sharedArray[1] = M;
    sharedArray[2] = 0;
    sharedArray[3] = 0;

    for(i = 4; i < nProducer*2+4; i++)
        sharedArray[i] = 0; 

    //TODO:Fill in your code here for additional initialization


    semInfoStruct mutex;
    semInfoStruct fillCount;
    semInfoStruct emptyCount;

    newSemaphore(&mutex);
    newSemaphore(&fillCount);
    newSemaphore(&emptyCount);

    sem_init(mutex.semPtr, 1, 1);
    sem_init(fillCount.semPtr, 1, 0);
    sem_init(emptyCount.semPtr, 1, BUFFERSIZE);

    for( i = 0; i < totalChild; i++){
        result = fork();
        if (result == 0) {
            if (i < nProducer){
                Producer(i, &sharedArray[0], 
                                &sharedArray[2],
                                &sharedArray[4],
                                &sharedArray[4+2*nProducer],
                            &mutex, &fillCount, &emptyCount);
                
            } else {
                Consumer(i-nProducer, &sharedArray[1],
                                &sharedArray[3],
                                &sharedArray[4+nProducer],
                                &sharedArray[4+2*nProducer],
                            &mutex, &fillCount, &emptyCount);

            }
            /*Important: Remember to detach the shared memory region*/
            shmdt( (char*)sharedArray );

            //Dont remove this return! Prevent child from running fork()!
            return 0;   //child ends here
        }
    }
    
    
    for( i = 0; i < totalChild; i++){
        wait( NULL );
    }

    //Perform Auditing
    //Do NOT change this part
    printf("Auditing Details:\n");
    for (i = 0; i < nProducer; i++){
        printf("\tProducer[%i] made %i items: Consume Count %i\n", 
            i, sharedArray[4+i], sharedArray[4+nProducer+i]);
        if ( sharedArray[4+i] == sharedArray[4+nProducer+i])
            printf("\t\tCORRECT\n");
        else
            printf("\t\tWRONG!!\n");
    }
    
    /*Important: Remember to remove the shared memory region after use!*/
    shmctl(shdMemId, IPC_RMID, NULL); 

    return 0;
}
