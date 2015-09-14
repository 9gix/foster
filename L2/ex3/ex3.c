/*************************************
* Lab 2 Exercise 3
* Name:
* Matric No:
* Lab Group:
*************************************/

//Note that the spcific header files may be different across Linux,
//Solaris or BSD (Mac OS). do a "man XXXX" to check what are the correct
//header files on your system. The given header files are for Linux.

//Remember to use the Linux version in your submission as we will mark
//your assingmnet on Linux :-)

#include <stdio.h>
#include <stdlib.h>     //For EXIT_FAILURE and atoi
#include <fcntl.h>      //For stat()
#include <sys/types.h>   
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>     //for fork(), wait()
#include <string.h>
#include <signal.h>     //for kill()



int main()
{
    const int ARGS_COUNT = 4;
    char request;
    int result;
    char * token;
    char leftover[40];  //for cleaning up the left over inputs
    int status;
    int i;
    struct stat sb;

    //read user input
    printf("YWIMC > ");
    scanf("%c", &request);
    while (request != 'Q'){
        fgets(leftover, 40, stdin); //clean up left over to ready for
                                    // next input
        token = strtok(leftover, " \n");
        char * args[4];
        for (i = 0; i < ARGS_COUNT; i++){
            args[i] = strtok(NULL, " \n");
        }            

        // Handle 'R' request
        if (request == 'R'){
            if (stat(token, &sb) == 0){
                result = fork();
                if (result == 0){
                    execl(token, "ex3", args[0], args[1], args[2], args[3], NULL);
                    _exit(EXIT_FAILURE);
                } else {
                    wait(&status);
                    printf("\n");
                }
            } else {
                printf("%s not found\n\n", token);
            }
        } else if (request == 'B') {
            if (stat(token, &sb) == 0){
                result = fork();
                if (result == 0){
                    execl(token, "ex3", args[0], args[1], args[2], args[3], NULL);
                    _exit(EXIT_FAILURE);
                } else {
                    printf("Child %i in background\n", result);
                }
            } else {
                printf("%s not found\n\n", token);
            }
        } else if (request == 'W') {
            
            int pid = atoi(token);

            if (kill(pid, 0) == 0){ // Check if PID is running by sending Sig 0 (no signal), it return 0 if signal successful.
                waitpid(pid, &status, 0);
            } else {
                printf("%i not a valid child\n\n", pid);
            }
        } else {
            printf("unknown instruction\n\n");
        }

        printf("YWIMC > ");
        scanf("%c", &request);
    }
    printf("Goodbye!\n");
    return 0;

}
