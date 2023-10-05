#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
	char *file = "ticket.txt";
	int fd = open(file, O_CREAT | O_RDWR, 0777);
	if(fd == -1) {
		perror("Failed to open file\n");
		exit(1);
	}

	key_t key = ftok(".", 'c');
	if(key == -1) {
		perror("Failed to get key\n");
		exit(1);
	}

	union semun {
		int val;
		struct semids_ds *buf;
		unsigned short *array;
	} sem;

	int id = semget(key, 1, 0);
	if(id == -1) {
		id = semget(key, 1, IPC_CREAT | 0777);
		if(id == -1) {
			perror("Failed to create semaphore\n");
			exit(1);
		}
		sem.val = 1;
		int status = semctl(id, 0, SETVAL, sem);
		if(status == -1) {
			perror("Failed to initialize Semaphore\n");
			exit(1);
		}
	}

	struct sembuf op;
	op.sem_num = 0;
	op.sem_flg = SEM_UNDO;

	printf("Press enter to enter into critical section\n");
	getchar();

	op.sem_op = -1;
	
	int status = semop(id, &op, 1);
	if(status == -1) {
		perror("Failed to lock for some reason\n");
		exit(1);
	}

	printf("obtained the lock\n");
	int ticket;
	int c = read(fd, &ticket, sizeof(ticket));
	if(c == 0) {
		ticket = 1;
	}
	else {
		ticket += 1;
		lseek(fd, 0, SEEK_SET);
	}

	write(fd, &ticket, sizeof(ticket));

	lseek(fd, 0, SEEK_SET);
	read(fd, &ticket, sizeof(ticket));
	printf("Ticket number is: %d\n", ticket);

	printf("Press enter to release lock\n");
	getchar();

	op.sem_op = 1;
	
	status = semop(id, &op, 1);
        if(status == -1) {
                perror("Failed to unlock for some reason but IPC_UNDO must have taken care of it\n");
                exit(1);
        }
	
	close(fd);

	return 0;
}
