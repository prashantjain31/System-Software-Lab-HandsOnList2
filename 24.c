#include<sys/ipc.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<stdlib.h>

int main() {
	key_t key = ftok(".", 'a');
	if(key == -1) {
		perror("Failed to create unique key\n");
		exit(1);
	}

	int id = msgget(key, IPC_CREAT | IPC_EXCL | 0777);
	if(id == -1) {
		perror("Failed to create message queue\n");
		exit(1);
	}

	
	printf("Key is: %d\n", key);
	printf("Message queue Id: %d\n", id);
	return 0;
}
