#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define PORT 9999
#define SIZE 16

char* getAnswer(char* input);

int main()
{
	int server = 0;
	int client = 0;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	socklen_t size;
	char input[SIZE];
	char* output;
	int n;

	server = socket(AF_INET, SOCK_STREAM, 0);

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(PORT);

	bind(server, (struct sockaddr*) &serverAddress, sizeof(serverAddress)); 

	listen(server, 1);
	printf("Listening on port %d...\n", PORT);

	while (1)
	{
		size = sizeof(clientAddress);
		client = accept(server, (struct sockaddr*) &clientAddress, &size); 
		printf("A new client from %s:%d!\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
		
		while ((n = read(client, input, sizeof(input))) > 0)
		{
			input[n - 1] = '\0';

			output = getAnswer(input);
			write(client, output, strlen(output));
		}
		
		close(client);
	}
	
	close(server);
	
	return 0;
}

char* getAnswer(char* input)
{
	char output[SIZE];

	sprintf(output, "You said %s\n", input);
	
	return strdup(output);
}
