#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TESTS 10

void divisors(int n)
{
	int i;

	if (n < 0)
	{
		printf("I don't like negative numbers!\n");
		return;
	}
		
	printf("Divisors of %d:", n);
	
	if (n == 0)
		printf(" none\n");
	else
	{
		for (i = 1; i <= n; ++i)
			if (n % i == 0)
				printf(" %d", i);
		printf("\n");
	}
}

int main()
{
	int i;
	int r;
	
	srand(42);
	
	for (i = 0; i < TESTS; ++i)
	{
		r = rand() % 1000;
		divisors(r);
	}
	
	return 0;
}
