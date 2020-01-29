#include <stdio.h>

int main()
{
	int x[] = {1, 2, 3};
	int secret = 42;
	unsigned int i;
	
	for (i = 0; i < sizeof(x); ++i)
		printf("%d\n", x[i]);
	
	return 0;
}
