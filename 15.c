/*
============================================================================
Name : 15.c
Author : Prashant Jain
Description : Write a simple program to send some data from parent 
	to the child process.
============================================================================
*/
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main() {
	int fd[2];
	char *buf = "Hello from parent to the children";
	int stat = pipe(fd);
	char *n;
	if(stat == -1) {
		perror("Couldn't create pipe\n");
		exit(1);
	}
	if(!fork()) {
		close(fd[1]);
		read(fd[0], &n, sizeof(buf));
		printf("Message from parent: %s\n", n);
	} else {
		close(fd[0]);
		write(fd[1], &buf, sizeof(buf));
	}
	wait(0);
	return 0;
}
