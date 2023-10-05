/*
============================================================================
Name : 31_b.c
Author : Prashant Jain
Description : Write a program to create a semaphore and initialize 
	value to the semaphore.
	b. create a counting semaphore
============================================================================
*/
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	key_t key = ftok(".", 'b');
	if(key == -1) {
		perror("Failed to create the key\n");
		exit(1);
	}

	int id = semget(key, 1, IPC_CREAT | 0777);
	if(key == -1) {
                perror("Failed to create the semaphore\n");
                exit(1);
        }

	union semun {
		int val;
	} sem;

	sem.val = 10;

	printf("Press enter to initialize semaphore\n");
	getchar();

	int status = semctl(id, 0, SETVAL, sem);
	if(status == -1) {
                perror("Faied to initialize semaphore\n");
                exit(1);
        }

	return 0;
}
