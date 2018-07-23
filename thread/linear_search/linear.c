#include "linear.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t mutex;


volatile static int res=-1;

int linear_search(int *arr, int first_index, int last_index, int key)
{
	
		for(int i=first_index; i<=last_index; i++)
		{
			if(arr[i]==key)
			{
				res=i;
				break;
			}
		}
	
    return res;
}

int fill_arr_random(int *arr, int size)
{
	srand(time);
	
	for(int i=0; i<size; i++)
	{
		*(arr+i)=rand();
		//*(arr+i)=i;
	}
}



void *thread_function(void *arg)
{	 
	 int *arr=((struct info_for_thread *)arg)->arr;
	 int first_index=((struct info_for_thread *)arg)->first;
	 int last_index=((struct info_for_thread *)arg)->last;
	 int key=((struct info_for_thread *)arg)->key;
	 
	 
		for(int i=first_index; i<=last_index; i++)
		{
			if(arr[i]==key)
			{
				res=i;
				break;
			}
			if(res!=-1) 
			{
				break;
			}
		}
	
	 pthread_exit(NULL);
}

int linear_search_thread(int *arr, int size, int key, int count_threads)
{	
	res=-1;
	if(count_threads<=0 || size<=0 || count_threads<1) return -1;
	if(size<count_threads) count_threads=size;
	
	struct info_for_thread *info_thread=malloc((count_threads-1)*sizeof(struct info_for_thread));
	
	int step=size/count_threads;
	int first_tmp=step+1;
	pthread_t thread[count_threads-1];
	for(int i=0; i<count_threads-1; i++)
	{
		info_thread[i].arr=arr;
		info_thread[i].first=first_tmp;
		info_thread[i].last=(i==count_threads-2)?size-1:first_tmp+step-1;
		info_thread[i].key=key;
		first_tmp+=step;
		
		pthread_create((thread+i), NULL, thread_function, (info_thread+i));	
	}		

		for(int i=0; i<=step==size?step-1:step; i++)
		{
			if(arr[i]==key)
			{
				res=i;
				break;
			}
			if(res!=-1) 
			{
				break;
			}
		}
	
	
	for(int i=0; i<count_threads-1; i++)
	{
		pthread_join(thread[i], NULL);
	}
	
	free(info_thread);
	
	return res;
}

