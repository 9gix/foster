#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    printf("First Call\n");
    int var = 1234;

    int result, id, childResult;

    result = fork();


    if (result != 0){

        printf("Parent Here: My id is %i\n", getpid());
        sleep(2);
        var++;
        printf("Parent Here: My child ID is %i\n", result);
        // id = wait(NULL); // block until all child finish processing
        id = wait(&childResult);
        printf("Parent: Child [%d] exited with %d \n", id, childResult);

    } else {
        printf("Child here: My id is %i\n", getpid());
        var--;
        sleep(2);
        printf("Child here: parent id is %i\n", getppid());
        return 999;
    }

    printf("Last Call\n");
    return 0;
};
