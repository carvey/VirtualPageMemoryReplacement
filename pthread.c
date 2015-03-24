#include <pthread.h>
#include <stdio.h>

void *inc_x(void *x_void_ptr);
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int main()
{
	

	int x=0, y=0;
	printf("x: %d, y: %d\n", x, y);

	pthread_mutex_lock(&m);
	pthread_t inc_x_thread;

	if (pthread_create(&inc_x_thread, NULL, inc_x, &x))
	{
		fprintf(stderr, "Error creating thread \n");
		return 1;
	}

	pthread_t inc_y;
	pthread_create(&inc_y, NULL, inc_x, &y);

	// pthread_mutex_lock(&m);
	while (++y < 10)
	{
		printf("current val for y is: %d using thread %ld \n", y, pthread_self());
	}
	pthread_mutex_unlock(&m);

	printf("y increment finished\n");

	if (pthread_join(inc_x_thread, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	printf("x: %d, y: %d\n", x, y);
	return 0;
	
}

void *inc_x(void *x_void_ptr)
{
	pthread_mutex_lock(&m);

	int *x_ptr = (int *)x_void_ptr;
	while(++(*x_ptr) < 10)
	{
		printf("current val for x is %d, incremented by %ld\n", *x_ptr, pthread_self());
	}
	printf("x increment finished \n");

	pthread_mutex_unlock(&m);
	return NULL;
}

// void *inc_y(void *y_void_ptr)
// {
// 	// pthread_mutex_lock(&m);

// 	int *y_ptr = (int *)y_void_ptr;
// 	while(++(*x_ptr) < 10)
// 	{
// 		printf("current val for x is %d, incremented by %ld\n", *y_ptr, pthread_self());
// 	}
// 	printf("y increment finished \n");

// 	pthread_mutex_unlock(&m);
// 	return NULL;

// }