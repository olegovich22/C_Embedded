#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "reverse_matrix.h"

/**
 * timespec_diff() - returns time difference in milliseconds for two timespecs.
 * @stop:	time after event.
 * @start:	time before event.
 *
 * Uses difftime() for time_t seconds calcultation.
 */

double timespec_diff(struct timespec *stop, struct timespec *start)
{
	double diff = difftime(stop->tv_sec, start->tv_sec);
	diff *= 1000;
	diff += (stop->tv_nsec - start->tv_nsec) / 1e6;
	return diff;
}

int main(int argc, char *argv[]) {
	
	if(argc<2) {printf("Error: no arguments provided\n"); return 1;} //i think this method better than goto
	if(argc>3) {printf("Error: too much arguments\n"); return 1;} 

    bool allow=(argc==3)?true:false;

    int size=atoi(argv[1]);
    if(size<2) {printf("Error: matrix size cant be less than 2\n"); return 1;}

    matrixAndSize *aMatrix=createMatrix(size);
    if(aMatrix==NULL) {printf("Error: haven't enough memory\n"); return 1;}

    addNumbToMatrix(aMatrix);

	if(allow)
	{
		printf("Your matrix\n");
		print_matrix(aMatrix);
		printf("\n");
		}
    
	
	struct timespec time_now, time_after;
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_now);
    int check=reverseMatrix(aMatrix);
    if(check==-1) return 1;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_after);

	if(allow)
	{
		printf("Revers matrix\n");
		print_matrix(aMatrix);
		}
    
    
    printf("Reverse  matrix with size %d took %g ms\n", size, timespec_diff(&time_after, &time_now));

    return 0;
}
