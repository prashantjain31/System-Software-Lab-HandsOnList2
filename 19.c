/*
============================================================================
Name : 19.c
Author : Prashant Jain
Description : Create a FIFO file by
	a. mknod command
	b. mkfifo command
	c. use strace command to find out, which command 
	   (mknod or mkfifo) is better.
	c. mknod system call
	d. mkfifo library function
============================================================================
*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

int main() {
	int stat = mkfifo("myFifo", 0777);
	if(stat == -1) {
		perror("fifo creation failed\n");
		exit(1);
	} else {
		printf("FIFO Success!!!");
	}

	stat = mknod("mknod", S_IFIFO, 0);
	if(stat == -1) {
                perror("FiFO creation using mknod failed\n");
                exit(1);
        } else {
                printf("mknod FIFO Success!!!");
        }

	
	return 0;
}
