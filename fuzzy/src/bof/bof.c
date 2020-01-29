#include <stdio.h>

int main()
{
	char x[4];
	
	printf("main() is at %p\n", main);

	sprintf(x, "%s%s", "hi", "!!!");
	printf("A nice greeting: %s\n", x);

	return 0;
}
