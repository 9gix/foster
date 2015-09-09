#include <stdio.h>

/* 
A short program to show all command line arguments
*/

int main(int argc, char* argv[])
{
    int i;

    for(i = 0; i < argc; i++){
        printf("Arg %i: %s\n",i+1, argv[i]);
    }

    return 0;
}
