#include <stdio.h>

char x[] = "Hello world!\n";

void print()
{
	char y[] = "%s";
	
	printf(y, x);
}

int main()
{
	print();

	return 0;
}
