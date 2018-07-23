#include "linear.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

double timespec_diff(struct timespec *stop, struct timespec *start)
{
	double diff = difftime(stop->tv_sec, start->tv_sec);
	diff *= 1000;
	diff += (stop->tv_nsec - start->tv_nsec) / 1e6;
	return diff;
}

 //int res=-1;
 
 //void *thread_function(void *arg)
 //{
	 //int tmp_res=linear_search(((struct info_for_thread *)arg)->arr, ((struct info_for_thread *)arg)->first, ((struct info_for_thread *)arg)->last, ((struct info_for_thread *)arg)->key);
	
	 //if(tmp_res!=-1) res=tmp_res;
//}


int main(int argc, char *argv[])
{
		struct timespec time_now, time_after;
		srand(time);
		int size=atoi(argv[1]);
		int count_threads=atoi(argv[2]);
		int *arr=malloc(size*sizeof(int));
        if(arr==NULL) {printf("NO MEMORY\n"); return 1;}		
		fill_arr_random(arr, size);
		int index=4;
		int key=arr[index];
		
		
		clock_gettime(CLOCK_REALTIME, &time_now);
		linear_search2(arr, 0, size-1, key);
		clock_gettime(CLOCK_REALTIME, &time_after);
		printf("%g\n", timespec_diff(&time_after, &time_now));
		
		clock_gettime(CLOCK_REALTIME, &time_now);
	
		int res22=linear_search_thread(arr, size, key, count_threads);
		
		clock_gettime(CLOCK_REALTIME, &time_after);
		printf("%g\n", timespec_diff(&time_after, &time_now));
		
		printf("res: %d, arr[res]: %d, index: %d, key: %d\n", res22, arr[res22], index, key);
		
		
		free(arr);
		return 0;
}
