/*
============================================================================
Name : 16.c
Author : Prashant Jain
Description : Write a program to send and receive data from parent to 
	child vice versa. Use two way communication.
============================================================================
*/
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main() {
	int cToP[2], pToC[2];
	int stat1, stat2;
	char *writeBuffer, *readBuffer;
	stat1 = pipe(cToP);
	stat2 = pipe(pToC);

	if(stat1 == -1 || stat2 == -1) perror("Couldn't create the pipe!");
	else {
		if(!fork()) {
			close(pToC[1]);
			close(cToP[0]);

			read(pToC[0], &readBuffer, sizeof(writeBuffer));
			printf("The parent's message: %s\n", readBuffer);
			
			writeBuffer = "Hi from child";
			write(cToP[1], &writeBuffer, sizeof(writeBuffer));
        	}
        	else {
            		close(pToC[0]);
            		close(cToP[1]); 

            		writeBuffer = "Hi from parent";
            		write(pToC[1], &writeBuffer, sizeof(writeBuffer));

            		read(cToP[0], &readBuffer, sizeof(writeBuffer));
            		printf("The child's message: %s\n", readBuffer);
        	}
    	}
    	wait(0);
    	return 0;
}
