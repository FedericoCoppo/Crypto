#include <stdio.h>

int main(int argc, char* argv[])
{
	FILE* f;
	int a;
	int b;
	int r;
	char o;
	
	f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("Unable to open the file %s!\n", argv[1]);
		
		return -1;
	}
	
	while ((r = fscanf(f, "%d %c %d\n", &a, &o, &b)) != EOF)
		if (r != 3)
		{
			printf("Invalid format!\n");
			fclose(f);
			
			return -1;
		}
		else if (o == '+')
			printf("%4d %c %4d = %4d\n", a, o, b, a + b);
		else if (o == '-')
			printf("%4d %c %4d = %4d\n", a, o, b, a - b);
		else if (o == '*')
			printf("%4d %c %4d = %4d\n", a, o, b, a * b);
		else if (o == '/')
			printf("%4d %c %4d = %4d\n", a, o, b, a / b);
		else
		{
			printf("The operator %c is unkown!\n", o);
			fclose(f);
			
			return -1;
		}
	
	fclose(f);
	
	return 0;
}
