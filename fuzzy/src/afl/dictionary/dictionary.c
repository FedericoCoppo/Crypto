#include <stdio.h>
#include <string.h>

#define SIZE 1024

int main(int argc, char* argv[])
{
	FILE* f;
	char x[SIZE];
	
	f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("Unable to open the file %s!\n", argv[1]);
		
		return -1;
	}
	
	if (fscanf(f, "%s", x) == 1)
	{
		if (strcmp(x, "one") == 0)
			printf("1\n");
		else if (strcmp(x, "tow") == 0)
			printf("2\n");
		else if (strcmp(x, "three") == 0)
			printf("3\n");
		else if (strcmp(x, "four") == 0)
			printf("4\n");
		else
			printf("I have no idea!\n");
	}
	else
		printf("The input file format is wrong!\n");

	fclose(f);
	
	return 0;
}
