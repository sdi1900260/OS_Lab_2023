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

union semnum{
	int val;
	struct semid_ds *buff;
	unsigned short *array;
	};

int main(){
	int shmid, semid;
	char line[128], *shmem;
	struct sembuf oper[1] = {{0, 1, 0}};
	union semnum arg;

	/* create/access shared memory segment */
	if ((shmid = shmget (SHMKEY, SHMSIZE, PERMS | IPC_CREAT)) < 0) {
		perror("shmget");
		exit(1);
	}
	printf("Creating shared memory with ID: %d\n", shmid);

	/* create a semaphore */
	if ((semid = semget(SEMKEY, 1, PERMS| IPC_CREAT)) <0) {
		perror("semget");
		exit(1);
	}
	printf("Creating a semaphore with ID: %d \n", semid);

	arg.val=0;

	/* initialize semaphore for locking */
	if (semctl(semid, 0, SETVAL, arg) <0) {
		perror("semctl");
		exit(1);
	}
	printf("Initializing semaphore to lock\n");
	getchar();

	if ((shmem = shmat(shmid, NULL, 0)) == (void *) -1) {
		perror("shmem");
		exit(1);
	}
	printf("Attaching shared memory segment \nEnter a string: ");
	fgets(line, sizeof(line), stdin);
	line[strlen(line)-1]='\0';

	/* Write message in shared memory */
	strcpy(shmem, line); 

	printf("Writing to shared memory region: %s\n", line);

	/* Make shared memory available for reading */
	if (semop(semid, &oper[0], 1) < 0) {
		perror("semop"); 
		exit(1);
	}
	shmdt(shmem);
	printf("Releasing shared memory region\n");
}
