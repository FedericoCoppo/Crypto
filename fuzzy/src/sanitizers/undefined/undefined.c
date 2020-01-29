#include <stdio.h>
#include <limits.h>

int main()
{
	int x = 1;
	int y = -1;
	
	x += INT_MAX;
	printf("A very nice number: %d\n", x);
	
	x <<= y;
	printf("Another very nice number: %d\n", x);
	
	return 0;
}
