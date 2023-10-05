#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>

void communicate(int *clientConnection) {
	int clientConnectionFD = *clientConnection;
	char data[100];
        int c = read(clientConnectionFD, data, 100);
	if(c == -1) perror("failed to get data\n");
        else printf("data from client: %s\n", data);
        write(clientConnectionFD, "Hello from server", 17);
        close(clientConnectionFD);
}

int main() {
	int socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFD == -1) {
		perror("Error Creating socket\n");
		exit(1);
	}
	
	struct sockaddr_in server, client;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);

	int bindStat = bind(socketFD, (struct sockaddr *) &server, sizeof(server));
	if(bindStat == -1) {
		perror("Error while binding name\n");
		exit(1);
	}

	int listenStat = listen(socketFD, 10);
	if(listenStat == -1) {
		perror("Failed to listen for incoming request\n");
		exit(1);
	}
	
	pthread_t threadID;
	int clientConnectionFD;
	while(1) {
		printf("Accepting connections: %d\n", getpid());
		int clientSize;
		clientConnectionFD = accept(socketFD, (struct sockaddr *) &client, &clientSize);
		if(clientConnectionFD == -1) {
			perror("Failed to accept the connection\n");
		} else {
			if(pthread_create(&threadID, NULL, (void *)communicate, &clientConnectionFD)) {
				perror("Error while creating thread\n");
			}
		}
	}
	close(socketFD);

	return 0;
}
