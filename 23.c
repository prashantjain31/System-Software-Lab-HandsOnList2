#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
	long maxOpen, size;
	size = pathconf("myFifo", _PC_PIPE_BUF);
	maxOpen = sysconf(_SC_OPEN_MAX);

	printf("Max size of pipe is: %ld and max number of files which can be opened in a process is: %ld\n", size, maxOpen);

	return 0;
}
