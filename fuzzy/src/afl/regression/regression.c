#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15

int oldFunction(int a, int b)
{
	return a + b;
}

int newFunction(int a, int b)
{
	if (b > 10)
		return a - b;
	else
		return a + b;
}

int main(int argc, char* argv[])
{
	FILE* f;
	int a;
	int b;
	int c1;
	int c2;
	int *p = NULL;
	
	f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("Unable to open the file %s!\n", argv[1]);
		
		return -1;
	}
	
	if (fscanf(f, "%d %d", &a, &b) != 2)
	{
		printf("Invalid format!\n");
		fclose(f);
		
		return -1;
	}
	
	c1 = oldFunction(a, b);
	c2 = newFunction(a, b);
	
	printf("Old result: %d\n", c1);
	printf("New result: %d\n", c2);
	
	if (c1 != c2)
	{
		printf("Dieeee!!!\n");
		*p = 1;
	}

	fclose(f);
	
	return 0;
}
