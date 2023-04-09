#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char** argv) {
	
	int clientSocket, message, closeMessage;
	int portNumber = atoi(argv[2]);
	struct sockaddr_in serverAddress;
	struct hostent* server;

	char buffer[256];
	if (argc < 3) {
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0)
		error("Error opening socket.");

	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr, "Error, %s could not be found.", argv[1]);
		
	}

	bzero((char*) &serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	bcopy((char*) server->h_addr, (char*) &serverAddress.sin_addr.s_addr, server->h_length);
	serverAddress.sin_port = htons(portNumber);
	if (connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
		error("Connection has failed");
	}

	while (1) {
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);
		message = write(clientSocket, buffer, strlen(buffer));
		if ( message < 0) 
			error("Error on writing.");
		bzero(buffer, 255);
		message = read(clientSocket, buffer, 255);
		if (message < 0)
			error("Error on reading");
		printf("Server: %s", buffer);
		closeMessage = strncmp("bye", buffer, 3);
		if (closeMessage == 0)
			break;
	}
	close(clientSocket);
	return 0;
}
