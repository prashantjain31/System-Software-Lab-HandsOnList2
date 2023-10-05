#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
	int socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFD == -1) {
		perror("Failed to create socket\n");
		exit(1);
	}

	struct sockaddr_in client;
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	client.sin_family = AF_INET;
	client.sin_port = htons(8080);

	int connectionStat = connect(socketFD, (struct sockaddr *)&client, sizeof(client));
	if(connectionStat == -1) {
		perror("Failed to connect to server\n");
		exit(1);
	}
	
	printf("Press enter to communicate with server\n");
	getchar();

	write(socketFD, "Hello from the client", 21);
	char data[100];
	read(socketFD, data, sizeof(data));
	printf("Data from the server: %s\n", data);

	close(socketFD);

	return 0;
}
