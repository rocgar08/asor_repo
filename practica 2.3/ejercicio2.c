#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>
#include <sched.h>


int main(int argc, char **argv){


	struct sched_param param;
	
	int options = sched_getscheduler(getpid());

	switch(options){
		case SCHED_FIFO: printf("FIFO \n"); break;
		case SCHED_RR: printf("RR \n");break;
		case SCHED_OTHER: printf("Other \n"); break;
		default: printf("Somthing went wrong \n"); break;
	}

	sched_getparam(getpid(),&param);
	
	int max = sched_get_priority_max(options);
	int min = sched_get_priority_min(options);

	printf("max priority %i\n", max);
	printf("min priority %i\n",min);

	return 0;
}

