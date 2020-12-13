#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>
#include <sched.h>


int main(int argc, char **argv){

	int val = atoi(argv[1]);

	if(argc!=2){
		printf("Error");
		return -1;
	}

	struct sched_param param;
	int options = sched_getscheduler(val);

	switch(options){
		case SCHED_FIFO: printf("FIFO \n"); break;
		case SCHED_RR: printf("RR \n");break;
		case SCHED_OTHER: printf("Other \n"); break;
		default: printf("Somthing went wrong \n"); break;
	}

	printf("max priority %i\n", sched_get_priority_max(val));
	printf("min priority %i\n",sched_get_priority_min(val));
	return 0;
}

