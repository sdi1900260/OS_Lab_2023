#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHMKEY (key_t)4321
#define SEMKEY (key_t)9876
#define SHMSIZE 256
#define PERMS 0600

int main(){
	int shmid, semid;
	char *shmem;
	struct sembuf oper[1] = {{0, -1, 0}};

	/* create/access shared memory segment */
	if ((shmid = shmget (SHMKEY, SHMSIZE, PERMS)) < 0) {
		perror("shmget");
		exit(1);
	}
	printf("Accessing shared memory with ID: %d\n", shmid);

	/* accessing a semaphore */
	if ((semid = semget(SEMKEY, 1, PERMS )) <0) {
		perror("semget");
		exit(1);
	}
	printf("Accessing semaphore with ID: %d \n", semid);

	if ((shmem = shmat(shmid, NULL, 0)) == (void *) -1) {
		perror("shmat");
		exit(1);
	}
	printf("Attaching shared memory segment\n");

	printf("Asking for access to shared memory region \n");
	if (semop(semid, &oper[0], 1) <0)  {
		perror("semop"); 
		exit(1);
	}
	printf("Reading from shared memory region: %s\n", shmem);

	/* detach shared memeory */
	shmdt(shmem); 

	/* destroy shared memory */
	if (shmctl(shmid, IPC_RMID, (struct shmid_ds *)0 ) <0) {
		perror("semctl");
		exit(1);
	}
	printf("Releasing shared segment with identifier %d\n", shmid);

	/* destroy semaphore set */
	if (semctl(semid, 0, IPC_RMID, 0) <0 ) { 
		perror("semctl");
		exit(1);
	}
	printf("Releasing semaphore with identifier %d\n", semid);
}
