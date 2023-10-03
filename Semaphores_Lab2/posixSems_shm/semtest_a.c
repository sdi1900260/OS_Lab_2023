/* semtest3.c: POSIX Semaphore test example using shared memory */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SEGMENTSIZE sizeof(sem_t)
#define SEGMENTPERM 0666

int main(int argc, char **argv) 
{
	sem_t *sp;
	int retval;
	int id, err;

	/* Make shared memory segment. */
	id = shmget(IPC_PRIVATE, SEGMENTSIZE, SEGMENTPERM);
	if (id == -1) {
		perror("Creation");
	} else { 
		printf("Allocated %d\n", id);
	}
	/* Attach the segment. */
	sp = (sem_t *) shmat(id, NULL, 0);
	if ( sp == (void *) -1) { 
		perror("Attachment."); 
		exit(2);
	}

	/* Initialize the semaphore. */
	retval = sem_init(sp, 1, 4);
	if (retval != 0) {
		perror("Couldn't initialize.");
		exit(3);
	}

	retval = sem_trywait(sp);
	printf("Did trywait. Returned %d >\n", retval);
	getchar();

	retval = sem_trywait(sp);
	printf("Did trywait. Returned %d >\n", retval);
	getchar();

	retval = sem_trywait(sp);
	printf("Did trywait. Returned %d >\n", retval);
	getchar();

	sem_destroy(sp);

	/* Remove segment. */
	err = shmctl(id, IPC_RMID, 0);
	if (err == -1) {
		perror("Removal.");
	} else {
		printf("Removed. %d\n",err);
	}
	return 0;
}
