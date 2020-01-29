#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE* f;
	int x;
	
	f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("Unable to open the file %s!\n", argv[1]);
		
		return -1;
	}
	
	if (fscanf(f, "%d", &x) == 1)
	{
		if (x == 42)
		{
			printf("Your number is %d and I like it\n", x);
			printf("Waiting for infinity...\n");
			while (1);
		}
		else
			printf("Your number is %d and I don't like it\n", x);
	}
	else
		printf("The input file format is wrong!\n");

	fclose(f);
	
	return 0;
}
