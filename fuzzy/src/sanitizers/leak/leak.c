#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int main()
{
	int* x;
	int i;
	
	x = (int*) malloc(sizeof(*x) * SIZE);
	for (i = 0; i < SIZE; ++i)
	{
		x[i] = rand() % 100;
		printf("%d\n", x[i]);
	}
		
	return 0;
}
