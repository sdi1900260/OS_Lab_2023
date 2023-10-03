/* Example code using SysV calls for semaphores and shared memory */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Union semun */
union semun {
    int val;                  /* value for SETVAL */
    struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
    unsigned short *array;    /* array for GETALL, SETALL */
};

void free_resources(int shm_id, int sem_id) { 
    /* Delete the shared memory segment */
    shmctl(shm_id,IPC_RMID,NULL);
    /* Delete the semaphore */
    semctl(sem_id,0,IPC_RMID,0);
}

/* Semaphore P - down operation, using semop */
int sem_P(int sem_id) {
    struct sembuf sem_d;

    sem_d.sem_num = 0;
    sem_d.sem_op = -1;
    sem_d.sem_flg = 0;
    if (semop(sem_id, &sem_d, 1) == -1) {
        perror("# Semaphore down (P) operation ");
        return -1;
    }
    return 0;
}

/* Semaphore V - up operation, using semop */
int sem_V(int sem_id) {
    struct sembuf sem_d;

    sem_d.sem_num = 0;
    sem_d.sem_op = 1;
    sem_d.sem_flg = 0;
    if (semop(sem_id, &sem_d, 1) == -1) {
        perror("# Semaphore up (V) operation ");
        return -1;
    }
    return 0;
}

/* Semaphore Init - set a semaphore's value to val */
int sem_Init(int sem_id, int val) {
    union semun arg;

    arg.val = val;
    if (semctl(sem_id, 0, SETVAL, arg) == -1) {
        perror("# Semaphore setting value ");
        return -1;
    }
    return 0;
}

int main () { 
    int shm_id;
    int sem_id;
    int *sh;
    int pid;

    /* Create a new shared memory segment */
    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0660);
    if (shm_id == -1) {
        perror("Shared memory creation");
        exit(EXIT_FAILURE);
    }

    /* Create a new semaphore id */
    sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660);
    if (sem_id == -1) {
        perror("Semaphore creation ");
        shmctl(shm_id, IPC_RMID, (struct shmid_ds *) NULL);
        exit(EXIT_FAILURE);
    }

    /* Set the value of the semaphore to 1 */
    if (sem_Init(sem_id, 1) == -1) { 
        free_resources(shm_id, sem_id);
        exit(EXIT_FAILURE);
    }

    /* Attach the shared memory segment */
    sh = (int *) shmat(shm_id, NULL, 0);
    if (sh == NULL) {
        perror("Shared memory attach ");
        free_resources(shm_id, sem_id);
        exit(EXIT_FAILURE);
    }
    /* Setting shared memory to 0 */
    *sh = 0;

    /* New process */
    if ((pid = fork()) == -1) { 
        perror("fork");
        free_resources(shm_id, sem_id);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        /* Child process */
        printf("# I am the child process with process id: %d\n", getpid());
    } else {
        /* Parent process */
        printf("# I am the parent process with process id: %d\n", getpid());
        sleep(2);
    }

    printf("(%d): trying to access the critical section\n", getpid());
    sem_P(sem_id);
    printf("(%d): accessed the critical section\n", getpid());

    (*sh)++;
    printf("(%d): value of shared memory is now: %d\n", getpid(), *sh);

    printf("(%d): getting out of the critical section\n", getpid());
    sem_V(sem_id);

    printf("(%d): got out of the critical section\n", getpid());

    /* Child process */
    if (!pid) {
        exit(EXIT_SUCCESS);
    }

    /* Wait for child process */
    wait(NULL);

    /* Clear recourses */
    free_resources(shm_id,sem_id);

    return 0;
}
