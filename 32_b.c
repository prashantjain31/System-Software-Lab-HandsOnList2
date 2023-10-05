/*
============================================================================
Name : 32_b.c
Author : Prashant Jain
Description : Write a program to implement semaphore to protect 
	any critical section.
	b. protect shared memory from concurrent write access
============================================================================
*/
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
	
	key_t shmkey = ftok(".", 'a');
	if(shmkey == -1) {
		perror("Failed to create shmkey\n");
		exit(1);
	}

	key_t semkey = ftok(".", 'c');
	if(semkey == -1) {
		perror("Failed to get semaphore key\n");
		exit(1);
	}

	int shmid = shmget(shmkey, 10, IPC_CREAT | 0777);
	if(shmid == -1) {
		perror("Failed to create the shared memory\n");
		exit(1);
	}

	union semun {
		int val;
		struct semids_ds *buf;
		unsigned short *array;
	} sem;

	int semid = semget(semkey, 1, 0);
	if(semid == -1) {
		semid = semget(semkey, 1, IPC_CREAT | 0777);
		if(semid == -1) {
			perror("Failed to create semaphore\n");
			exit(1);
		}
		sem.val = 1;
		int status = semctl(semid, 0, SETVAL, sem);
		if(status == -1) {
			perror("Failed to initialize Semaphore\n");
			exit(1);
		}
	}

	char *shmpt = shmat(shmid, (void *) 0, 0);
	if(*shmpt == -1) {
		perror("Failed to retrieve the pointer to address space\n");
		exit(1);
	}

	struct sembuf op;
	op.sem_num = 0;
	op.sem_flg = SEM_UNDO;

	printf("Press enter to enter into critical section\n");
	getchar();

	op.sem_op = -1;
	
	int status = semop(semid, &op, 1);
	if(status == -1) {
		perror("Failed to lock for some reason\n");
		exit(1);
	}

	printf("obtained the lock\n");
	
	sprintf(shmpt, "Hiii");

	printf("Data in shared memory: %s\n", shmpt);

	printf("Press enter to release lock\n");
	getchar();

	op.sem_op = 1;
	
	status = semop(semid, &op, 1);
        if(status == -1) {
                perror("Failed to unlock for some reason but IPC_UNDO must have taken care of it\n");
                exit(1);
        }

	return 0;
}
