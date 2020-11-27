#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define INFINITY 1000000
int  main( int argc, char**argv){

	time_t t = time(NULL);
	struct timeval tm;

	gettimeofday(&tm,NULL);
	int start = tm.tv_usec;

	int i = 0, loop = 0;
	
	for( i; i <INFINITY; i++){
		gettimeofday(&tm,NULL);
		loop = tm.tv_usec;
	}
	printf("calculating loop time %i\n", loop-start);
	return 0;
}