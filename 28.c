/*
============================================================================
Name : 28.c
Author : Prashant Jain
Description : Write a program to change the exiting message 
	queue permission. (use msqid_ds structure)
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
	
	struct msqid_ds mQInfo;
	int status = msgctl(id, IPC_STAT, &mQInfo);
	if(status  == -1) {
		perror("Failed to get info\n");
		exit(1);
	} else {
		mQInfo.msg_perm.mode = 0766;
	}

	status = msgctl(id, IPC_SET, &mQInfo);
	if(status  == -1) {
                perror("Failed to set info\n");
                exit(1);
        }

	return 0;
}
