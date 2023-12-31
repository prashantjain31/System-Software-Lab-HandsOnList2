/*
============================================================================
Name : 20_r.c
Author : Prashant Jain
Description : Write two programs so that both can communicate by 
	FIFO -Use one way communication. Read End of one way communication.
============================================================================
*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
	int fd = open("myFifo", O_RDONLY);
	if(fd == -1) {
		perror("Couldn't open");
		exit(1);
	}

	char buf[100];
	int c = read(fd, buf, 100);
	printf("Message is %d character long and it says: %s\n", c, buf);
	return 0;
}
