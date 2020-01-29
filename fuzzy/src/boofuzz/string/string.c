#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define PORT 9999
#define SIZE 32

int authenticate(char* user, char* password);

int main()
{
	int server = 0;
	int client = 0;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	socklen_t size;
	char buffer[SIZE];
	char command[SIZE];
	char word[SIZE];
	char user[SIZE];
	char output[SIZE];
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

		while ((n = read(client, buffer, sizeof(buffer))) > 0)
		{
			buffer[n - 1] = '\0';
			printf("Read '%s'\n", buffer);
			
			if (n < 0 || sscanf(buffer, "%s %s", command, word) != 2)
				continue;
			
			if (strcmp(command, "user") == 0)
			{
				strcpy(user, word);
				sprintf(output, "hello %s\n", user);
				write(client, output, strlen(output));
			}
			else if (strcmp(command, "password") == 0)
			{
				if (authenticate(user, word))
				{
					sprintf(output, "welcome %s\n", user);
					write(client, output, strlen(output));
				}
				else
				{
					sprintf(output, "bye %s\n", user);
					write(client, output, strlen(output));
					close(client);
					break;
				}
			}
			else if (strcmp(command, "length") == 0)
			{
				sprintf(output, "answer %lu\n", strlen(word));
				write(client, output, strlen(output));
			}
			else if (strcmp(command, "isinteger") == 0)
			{
				int integer = 1;
				unsigned int i;
				
				for (i = 0; i < strlen(word); ++i)
					if (!isdigit(word[i]))
						integer = 0;

				if (integer)
					sprintf(output, "answer true\n");
				else
					sprintf(output, "answer false\n");
				write(client, output, strlen(output));
			}
			else if (strcmp(command, "double") == 0)
			{
				sprintf(output, "answer %s%s\n", word, word);
				write(client, output, strlen(output));
			}
			else if (strcmp(command, "bye") == 0)
			{
				sprintf(output, "bye %s\n", user);
				write(client, output, strlen(output));
				close(client);
				break;
			}
		}
	}

	close(server);
	
	return 0;
}

int authenticate(char* user, char* password)
{
	if (strcmp(user, "dani") == 0 && strcmp(password, "security") == 0)
		return 1;
	else
		return 0;
}
