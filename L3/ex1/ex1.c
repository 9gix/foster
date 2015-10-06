/*************************************
* Lab 3 Exercise 1
* Name: Eugene
* Student No: A0116631N
* Lab Group: 8
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  // For Predefined constants
#include <sys/ipc.h>    // For POSIX IPC
#include <sys/shm.h>    // For POSIX Shared Memory

int main()
{
    int result;
    int shdMemId;    
    char* shdMemRegion;
    int shdMemSize = 4096;  //Size in # of bytes

    int S, V;
    printf("Enter Array Size: ");
    scanf("%i", &S);
    printf("Enter Start Value: ");
    scanf("%i", &V);

    //Create a new shared memory region
    shdMemId = shmget( IPC_PRIVATE, shdMemSize, IPC_CREAT | 0666 );
    if (shdMemId < 0){
        printf("Cannot create shared memory region!\n");
        exit(1);
    }
    //printf("Shared Memory Id is %i\n",shdMemId);

    //Attach a new shared memory region
    shdMemRegion = (char*) shmat(shdMemId, NULL, 0);
    if ( shdMemRegion == (char*)-1){
        printf("Cannot attach shared memory region!\n");
        exit(1);
    }

    //Shared memory regions remained attached after fork()
    // Parent and child can now communicate with each other!
    result = fork();
    if (result){        //Parent

        int i;
        int* A = (int*) shdMemRegion;
        for (i = 0; i < S; i++){
            A[i] = V + i;
        }

        // Signal Child to compute
        A[S] = 9999;

        int parentSum = 0;
        for (i = (S/2); i < S; i++){
            parentSum = parentSum + A[i];
        }

        while (A[S+2] != 9999){
            sleep(0.5);
        }
        printf("Parent Sum = %i\n", parentSum);
        int childSum = A[S+1];
        printf("Child Sum = %i\n", childSum);
        int total = parentSum + childSum;
        printf("Total = %i\n", total);

        /*Important: Remember to detach the shared memory region*/
        shmdt( shdMemRegion );
    } else {            //Child
        int i;
        int* A = (int*) shdMemRegion;

        // Wait Parent signal to compute
        while (A[S] != 9999){
            sleep(0.5);
        }

        int childSum = 0;
        for (i = 0; i < (S/2); i++){
            childSum = childSum + A[i];
        }

        A[S+1] = childSum; // Address for child computation result
        A[S+2] = 9999; // Notify Parent that child computation is done

        /*Important: Remember to detach the shared memory region*/
        shmdt( shdMemRegion );

        return 0;   //Child Ends here

    }

    /*Important: Remember to remove the shared memory region after use!*/
    shmctl(shdMemId, IPC_RMID, NULL); 
    return 0;
}
