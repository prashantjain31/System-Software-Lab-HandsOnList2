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
