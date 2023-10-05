/*
============================================================================
Name : 21_a.c
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
	int fd = open("myFifo", O_WRONLY);
	int fd2 = open("myFifo2", O_RDONLY);
	if(fd == -1 || fd2 == -1) {
		perror("Couldn't open");
		exit(1);
	}

	char buf[100] = "Hello how are you!!";
	write(fd, &buf, sizeof(buf));
	read(fd2, &buf, 100);
	printf("Message received in a: %s\n", buf);
	return 0;
}
