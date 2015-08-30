#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    fork();
    execl("/bin/ls", "ls", "-l", NULL);
    return 0;
}
