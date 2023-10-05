/*
============================================================================
Name : 30.c
Author : Prashant Jain
Description : Write a program to create a shared memory.
	a. write some data to the shared memory
	b. attach with O_RDONLY and check whether you are able to overwrite.
	c. detach the shared memory
	d. remove the shared memory
============================================================================
*/
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	key_t key = ftok(".", 'a');
	if(key == -1) {
		perror("Failed to create key\n");
		exit(1);
	}
	
	ssize_t size = 10;
	int id = shmget(key, size, IPC_CREAT|0777);
	if(id == -1) {
		perror("Failed to create the shared memory\n");
		exit(1);
	}

	char *pt, *readpt;
	pt = shmat(id, (void *) 0, 0);
	if(*pt == -1) {
		perror("Error connecting to shared memory space\n");
		exit(1);
	}

	printf("Press enter to write\n");
	getchar();

	sprintf(pt, "Hii");

	printf("Press enter to read from shared memory\n");
	getchar();

	printf("Data inside shared memory: %s\n", pt);

	readpt = shmat(id, (void *)0, SHM_RDONLY);
	if(*readpt == -1) {
                perror("Error connecting to shared memory space\n");
                exit(1);
        }

	// printf("Press enter to write using read only pointer\n");
        // getchar();

        // sprintf(readpt, "Hii RD");

        printf("Press enter to read from shared memory\n");
        getchar();



        printf("Data inside shared memory: %s\n", readpt);

	printf("Pointer is being detached\n");
	shmdt(pt);
	shmdt(readpt);

	printf("Delete shared memory\n");
	shmctl(id, IPC_RMID, NULL);

	return 0;
}
