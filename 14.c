#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main() {
	int fd[2];
	char buf[100];
	int stat = pipe(fd);
	if(stat == -1) {
		perror("Couldn't create pipe\n");
		exit(1);
	}
	if(!fork()) {
		close(fd[1]);
		int c = read(fd[0], buf, sizeof(buf));
		printf("Message from parent: %s\n", buf);
	} else {
		close(fd[0]);
		printf("Enter message from parent to child: ");
		scanf("%[^\n]", buf);
		write(fd[1], &buf, sizeof(buf));
	}
	wait(0);
	return 0;
}
