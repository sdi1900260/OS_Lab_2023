/* Compile Using:
gcc -pthread -Werror -Wall thread-create.c -o thread-create
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <unistd.h>
#include <sys/syscall.h>

int randomNumber;
     
void* childThread (void* threadID)
{
	sleep(10 - (long)threadID);
    printf("Child Thread %ld (SYS_gettid: %d)is called with RANDOM %d\n", 
                (long)threadID, (unsigned int)syscall(SYS_gettid),randomNumber++);
	printf("Child Thread %ld (pthread_self: %u)is called with RANDOM %d\n", 
                (long)threadID, (unsigned int)pthread_self(),randomNumber++);
    return NULL;
}
/* The main program. */
int main ()
{
    pthread_t thread_id;
    long threadCount;
    srand(time(NULL));
    randomNumber = rand()%1000;
    /* Create a new thread. The new thread will run the childThread function. */
    for (threadCount = 1; threadCount < 10; threadCount++){
        pthread_create(&thread_id, NULL, &childThread, (void *)threadCount);
		printf("Parent has created thread: %u \n", (unsigned int)thread_id);
		}
    sleep(10);
    return 0;
}
