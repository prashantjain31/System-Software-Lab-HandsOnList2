#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
	key_t key = ftok(".", 'a');
	if(key == -1) {
		perror("failed to get key\n");
		exit(1);
	}

	int id = msgget(key, IPC_CREAT | 0777);
	struct msqid_ds mQInfo;
	if(id == -1) {
		perror("Failed to create message queue\n");
		exit(1);
	}

	int status = msgctl(id, IPC_STAT, &mQInfo);
	if(status == -1) {
		perror("Failed to get status\n");
		exit(1);
	}

	printf("Access Permission: %od\n", mQInfo.msg_perm.mode);
	printf("UID: %d\n", mQInfo.msg_perm.uid);
	printf("GID: %d\n", mQInfo.msg_perm.gid);
	printf("Time of last message sent: %ld and received: %ld\n", mQInfo.msg_stime, mQInfo.msg_rtime);
	printf("Time of last change in message queue: %ld\n", mQInfo.msg_ctime);
	printf("Size of Queue %ld\n", mQInfo.msg_cbytes);
	printf("Number of message in Queue: %ld\n", mQInfo.msg_qnum);
	printf("Maximum number of bytes allowed: %ld\n", mQInfo.msg_qbytes);
	printf("pid of msgsnd: %d and msgrcv: %d\n", mQInfo.msg_lspid, mQInfo.msg_lrpid);

	return 0;
}
