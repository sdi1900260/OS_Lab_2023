/* Compile Using:
gcc -pthread -Werror -Wall thread-create_return.c -o thread-create_return
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <unistd.h>

long sharedNumber = 0; 
     
void* childThread (void* threadID)
{	
    int i;
    // sleep((long)threadID);// Remove sleep() to see the effect of the race condition
    for (i = 0; i < 1000000; i++) {
        sharedNumber++;
    }
    printf("Child Thread %ld has computed RANDOM NUMBER: %ld\n", (long)threadID, sharedNumber);
    pthread_exit((void *)sharedNumber); // Return a Value to Main: Parent
}
/* The main program. */
int main ()
{
    pthread_t thread_id[10];	/* Store the threadIDs in an array */
    long threadCount;
	void *status;
    /* Create a new thread. The new thread will run the childThread function. */
    for (threadCount = 1; threadCount< 10; threadCount++){
        pthread_create (&thread_id[threadCount], NULL, &childThread, (void *)threadCount);
		printf("Parent has created thread %ld with thread_id %u \n", threadCount, (unsigned int)thread_id[threadCount]);
		pthread_join(thread_id[threadCount], &status); /* Join immediately after creation of the thread */
		}
	printf("Parent has CREATED ALL threads.\n");
	for (threadCount = 1; threadCount< 10; threadCount++) { /* Join after all thread creation */
		//pthread_join(thread_id[threadCount], &status);
		//printf("Parent: completed join with thread %ld having a status of %ld\n",threadCount,(long)status);
    }
	printf("Parent has WAITED FOR ALL threads to finish.\n");	
    //sleep(1);
    return 0;
}
