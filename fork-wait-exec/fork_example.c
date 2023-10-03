#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/wait.h>

int data = 472;

int main()
{
    int pid, status;
    printf("Before the fork. Data is %d\n", data);
    if ((pid = fork()) != 0) {
        // parent
        printf("I am the parent. Data is %d\n", data);
        sleep(1);   // suspend myself for 1 second
        data = 0;
        printf("I am the parent again. Data is %d\n", data);
    } else {
        // child
        printf("I am the child. Data is %d\n", data);
        sleep(2);   // suspend myself for 2 seconds
        printf("I am the child again. Data is %d\n", data);
        sleep(2);   // suspend myself for 2 seconds
        data = 444;
        printf("I am the child again. Data is %d\n", data);
    }
    wait(&status);
    //waitpid(pid, &status, 0);
    printf("Hello class!\n");
    return 1;
}