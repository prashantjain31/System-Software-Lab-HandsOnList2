#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
	key_t key = ftok(".", 'a');
	if(key == -1) {
		perror("Failed to get the key\n");
		exit(1);
	}

	int id = semget(key, 1, 0);
	if(id == -1) {
		perror("Failed to get the semaphore maybe it does not exist\n");
		exit(1);
	}

	int status = semctl(id, 0, IPC_RMID);
	if(status == -1) {
		perror("Failed to remove\n");
		exit(1);
	}

	return 0;
}
