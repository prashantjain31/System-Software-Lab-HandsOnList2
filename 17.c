/*
============================================================================
Name : 17.c
Author : Prashant Jain
Description : Write a program to execute ls -l | wc.
	a. use dup
	b. use dup2
	c. use fcntl
============================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

int main() {
	int fd[2];
	int stat = pipe(fd);
	if(stat == -1) {
		perror("Couldn't create the file\n");
		exit(1);
	}
	int ch;
	printf("Enter which one you want to use \n1.Dup \n2.Dup2 \n3.Fcntl: ");
	scanf("%d", &ch);
	if(!fork()) {
		close(1);
		close(fd[0]);
		if(ch == 1) {
			dup(fd[1]);
		} else if(ch == 2) {
			dup2(fd[1], 1);
		} else {
			fcntl(fd[1], F_DUPFD, 1);
		}
		execlp("ls", "ls", "-l", (char *)NULL);
	} else {
		close(0);
                close(fd[1]);
                if(ch == 1) {
                        dup(fd[0]);
                } else if(ch == 2) {
                        dup2(fd[0], 0);
                } else {
                        fcntl(fd[0], F_DUPFD, 0);
                }
                execlp("wc", "wc", (char *)NULL);
	}
	wait(0);
	return 0;
}
