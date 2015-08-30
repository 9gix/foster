#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[]){
    int i;

    for (i = 0; i < argc; i++){
        printf("Args %i: %s\n", i+1, argv[i]);
    }

    execl("/bin/ls", "ls", "-l", NULL);
    printf("Helloooooo\n");

    return 0;

};
