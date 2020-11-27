#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int  main( int argc, char**argv){

	time_t act = time(NULL);
	printf("The beginning:  %i\n",act);
	return 0;
}