/*************************************
* Lab 2 Exercise 1
* Name:
* Matric No:
* Lab Group:
*************************************/

#include <stdio.h>
#include <sys/types.h>   
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>     //for fork(), wait()

int main()
{
    int nChild, i, j, result;
    
    //Read the number of child
    scanf("%d", &nChild);
    pid_t pid_list[nChild];

    result = getpid();

    //Spawn child processes
    for (i = 0; i < nChild; i++){
        result = fork();
        if (result == 0){
            printf("Child %d[%d]: Hello!\n", i + 1, getpid());
            exit(0);
        } else {
            pid_list[i] = result;
        }
    }
    //Wait on child processes in order
    for (i = 0; i < nChild; i++){
        result = waitpid(pid_list[i]);
        for (j = 0; j < nChild; j++){
            if (pid_list[i] == pid_list[j]){
                break;
            }
        }
        printf("Parent: Child %d[%d] done.\n", j + 1, pid_list[i]);
    }
    printf("Exiting.\n");

      
    return 0;
}
