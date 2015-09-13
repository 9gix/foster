/*************************************
* Lab 2 Exercise 2
* Name: Eugene
* Matric No: A0116631
* Lab Group: 8
*************************************/

//Note that the spcific header files may be different across Linux,
//Solaris or BSD (Mac OS). do a "man XXXX" to check what are the correct
//header files on your system. The given header files are for Linux.

//Remember to use the Linux version in your submission as we will mark
//your assingmnet on Linux :-)
#include <stdio.h>
#include <stdlib.h>     //For EXIT_FAILURE
#include <fcntl.h>      //For stat()
#include <sys/types.h>   
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>     //for fork(), wait()
#include <string.h>

int main()
{
    char request;
    int result;
    char * token;
    char leftover[40];  //for cleaning up the left over inputs
    int status;

    //read user input
    printf("YWIMC > ");
    scanf("%c", &request);
    while (request != 'Q'){
        // Handle 'R' request

        if (request == 'R'){
            fgets(leftover, 40, stdin); //clean up left over to ready for
                                        // next input
            token = strtok(leftover, " \n");
            result = fork();
            if (result == 0){
                execl(token, "ex2", NULL);
                _exit(EXIT_FAILURE);
            } else {
                wait(&status);
            }
        }

        printf("YWIMC > ");
        scanf("%c", &request);
    }
    
    printf("Goodbye!\n");
    return 0;

}
