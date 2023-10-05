/*
============================================================================
Name : 21_b.c
Author : Prashant Jain
Description : Write two programs so that both can communicate by 
	FIFO -Use two way communications.
============================================================================
*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
	int fd = open("myFifo", O_RDONLY);
	int fd2 = open("myFifo2", O_WRONLY);
	if(fd == -1 || fd2 == -1) {
		perror("Couldn't open");
		exit(1);
	}

	char buf[100];
	read(fd, &buf, 100);
	printf("Message received in b: %s\n", buf);
	char buf2[] = "I am fine!!";
	write(fd2, buf2, sizeof(buf2));
	return 0;
}
