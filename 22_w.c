/*
============================================================================
Name : 22_w.c
Author : Prashant Jain
Description : Write a program to wait for data to be written into 
	FIFO within 10 seconds, use select system call with FIFO.
============================================================================
*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
	int fd = open("myFifo", O_WRONLY);
	if(fd == -1) {
		perror("Couldn't open");
		exit(1);
	}

	char buf[] = "Hello how are you!!";
	printf("Write is going to send data to read file\n");
	write(fd, &buf, sizeof(buf));
	return 0;
}
