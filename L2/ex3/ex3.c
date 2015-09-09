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
#include <fcntl.h>      //For stat()
#include <sys/types.h>   
#include <sys/stat.h>
#include <unistd.h>     //for fork(), wait()

int main()
{
    char request;
    char leftover[40];  //for cleaning up the left over inputs

    //read user input
    printf("YWIMC > ");
    scanf("%c", &request);
    while (request != 'Q'){
        // Handle 'R' request

        fgets(leftover, 40, stdin); //clean up left over to ready for
                                    // next input

        printf("YWIMC > ");
        scanf("%c", &request);
    }
    
    printf("Goodbye!\n");
    return 0;

}
