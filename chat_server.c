#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char* msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char** argv) {

	if (argc < 2) {
		fprintf(stderr, "Port number has not been provided, therefore program has been terminated.");
		exit(1);
	}

	
	int serverSocket, newSocket, message, closeMessage;
	int portNumber = atoi(argv[1]);
	char buffer[255];

	struct sockaddr_in serverAddress, clientAddress;
	socklen_t clientLength;

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		error("Error opening socket.");
	}

	bzero((char *) &serverAddress, sizeof(serverAddress));

	
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(portNumber);

	if (bind(serverSocket, (struct sockaddr* ) &serverAddress, sizeof(serverAddress)) < 0) {
		error("Binding has failed.");
	}

	listen(serverSocket, 5);
	clientLength = sizeof(clientAddress);

	newSocket = accept(serverSocket, (struct sockaddr*) &clientAddress, &clientLength);
	
	if (newSocket < 0) 
		error("Error on Accept.");

	while(1) {
		//reading messages from the client
		bzero(buffer, 255);
		message = read(newSocket, buffer, 255);
		if (message < 0)
			error("Error on reading message.");
		printf("Client: %s\n", buffer);

		//sending messages to the client
		fgets(buffer, 255, stdin);
		message = write(newSocket, buffer, strlen(buffer));
		if (message < 0) 
			error("Error on writing message.");
		
		closeMessage = strncmp("bye", buffer, 3);
		if (closeMessage == 0)
			break;
	}

	close(newSocket);
	close(serverSocket);
	return 0;
}


