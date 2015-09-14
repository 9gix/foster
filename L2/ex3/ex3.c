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
#include <stdarg.h>     //For va_list, va_start, va_arg, va_end
#include <fcntl.h>      //For stat()
#include <sys/types.h>   
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>     //for fork(), wait()
#include <string.h>
#include <signal.h>     //for kill()


/** Execute command in foreground and return 0 when command successfully started */
int executeJob(char* command, int arg_count, ... ) {    
    struct stat sb;
    int i, result, status_code, status;
    char* args[arg_count];

    va_list arguments;

    va_start(arguments, arg_count);

    
    for (i = 0; i < arg_count; i++) {
        args[i] = va_arg(arguments, char*);
    }
    va_end(arguments);

    if (stat(command, &sb) == 0){
        result = fork();
        if (result == 0){
            execl(command, "ex3", args[0], args[1], args[2], args[3], NULL);
            _exit(EXIT_FAILURE);
        } else {
            wait(&status);
            printf("\n");
        }
        status_code = 0;
    } else {
        printf("%s not found\n\n", command);
        status_code = 1;
    }
    return status_code;
}

/** Execute command in the background and return 0 when command successfully started */
int executeBackgroundJob(char* command, int arg_count, ... ) {    
    struct stat sb;
    int i, result, status_code;
    char* args[arg_count];

    va_list arguments;

    va_start(arguments, arg_count);

    
    for (i = 0; i < arg_count; i++) {
        args[i] = va_arg(arguments, char*);
    }
    va_end(arguments);

    if (stat(command, &sb) == 0){
        result = fork();
        if (result == 0){
            execl(command, "ex3", args[0], args[1], args[2], args[3], NULL);
            _exit(EXIT_FAILURE);
        } else {
            printf("Child %i in background\n", result);
        }
        status_code = 0;
    } else {
        printf("%s not found\n\n", command);
        status_code = 1;
    }

    return status_code;
}


/** Wait for background job and return 0 when process exist and ended */
int waitBackgroundJob(int pid){
    int status_code, status;
    if (kill(pid, 0) == 0){ // Check if PID is running by sending Sig 0 (no signal), it return 0 if signal successful.
        waitpid(pid, &status, 0);
        status_code = 0;
    } else {
        printf("%i not a valid child\n\n", pid);
        status_code = 1;
    }
    return status_code;
}
int main()
{
    const int ARGS_COUNT = 4;
    char request;
    char * token;
    char leftover[40];  //for cleaning up the left over inputs
    int i;

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
            executeJob(token, ARGS_COUNT, args[0], args[1], args[2], args[3]);
        } else if (request == 'B') {
            executeBackgroundJob(token, ARGS_COUNT, args[0], args[1], args[2], args[3]);
        } else if (request == 'W') {
            int pid = atoi(token);
            waitBackgroundJob(pid);
        } else {
            printf("unknown instruction\n\n");
        }

        printf("YWIMC > ");
        scanf("%c", &request);
    }
    printf("Goodbye!\n");
    return 0;

}
