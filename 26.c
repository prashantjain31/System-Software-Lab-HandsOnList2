/*
============================================================================
Name : 26.c
Author : Prashant Jain
Description : Write a program to send messages to the message queue. 
	Check $ipcs -q
============================================================================
*/
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	key_t key = ftok(".", 'a');
	if(key == -1) {
		perror("Failed to create key\n");
		exit(1);
	}

	int id = msgget(key, IPC_CREAT|0777);
	if(id == -1) {
		perror("Failed to create the message queue\n");
		exit(1);
	}

	struct msgbuf {
		long mtype;
		int num;
	};

	struct msgbuf msg;
	msg.mtype = 1;
	msg.num = 108;
	int status = msgsnd(id, &msg, sizeof(msg), 0);
	if(status  == -1) {
		perror("Failed to send the message\n");
		exit(1);
	} else {
		printf("Message Sent!!");
	}

	return 0;
}
