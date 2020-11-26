#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main (int argc, char **argv){
	
	int sid = setuid(0);
	//setuid sets the  effective  user ID of the calling process
	if (sid == -1){
		printf("Error is...",strerror(sid));
		return -1;
	}
	printf("No errors \n");
	return 0;
}
