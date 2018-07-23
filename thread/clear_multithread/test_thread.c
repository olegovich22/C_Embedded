#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <limits.h>


double timespec_diff(struct timespec *stop, struct timespec *start)
{
	double diff = difftime(stop->tv_sec, start->tv_sec);
	diff *= 1000;
	diff += (stop->tv_nsec - start->tv_nsec) / 1e6;
	return diff;
}

int molotyt()
{
	for(unsigned int i=0; i<20000000; i++);
}

void *thread_function(void *arg)
{
	molotyt();
}

int main(int argc, char *argv[])
{	
	int count_threads=atoi(argv[1]);
	
	struct timespec time_now, time_after;
	clock_gettime(CLOCK_REALTIME, &time_now);
	
	pthread_t thread[count_threads];
	for(int i=0; i<count_threads-1; i++)
	{	
		pthread_create((thread+i), NULL, thread_function, NULL);	
	}
	
	molotyt();
	
	for(int i=0; i<count_threads-1; i++)
	{
		pthread_join(thread[i], NULL);
	}
	
	clock_gettime(CLOCK_REALTIME, &time_after);
	printf("time in %d thread: %g\n", count_threads, timespec_diff(&time_after, &time_now));
	
	clock_gettime(CLOCK_REALTIME, &time_now);
	for(int i=0; i<count_threads; i++)
	{	
		molotyt();	
	}
	clock_gettime(CLOCK_REALTIME, &time_after);
	printf("time in 1 thread: %g\n", timespec_diff(&time_after, &time_now));
	
	return 0;
}
