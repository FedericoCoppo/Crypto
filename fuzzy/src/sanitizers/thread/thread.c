#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 10

int value;

void* function(void* v)
{
	sleep(rand() % 3);
	
	value = (intptr_t) v;
		
	return NULL;
}

int main()
{
	pthread_t threads[SIZE];
	int i;
	
	srand(time(NULL));
	
	for (i = 0; i < SIZE; ++i)
		pthread_create(&threads[i], NULL, function, (void*) (intptr_t) i);
	
	for (i = 0; i < SIZE; ++i)
		pthread_join(threads[i], NULL);
	
	printf("The value is %d\n", value);
     
	return 0;
}
