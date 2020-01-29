#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15

int main(int argc, char* argv[])
{
	FILE* f;
	char line[SIZE];
	
	f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("Unable to open the file %s!\n", argv[1]);
		
		return -1;
	}
	
	fgets(line, SIZE, f);

	if (strlen(line) >= SIZE - 1)
		strcat(line, "!!!");
	
	printf("Your string is %s\n", line);
	
	fclose(f);
	
	return 0;
}
