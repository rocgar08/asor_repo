#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX_ERRORS 255

int main (int argc, char **argv){
	
	
	//setuid sets the  effective  user ID of the calling process
	int i = 0, sid = 0;
	for ( i; i < MAX_ERRORS; i++){
		sid = setuid(i);
		if (sid == -1){
			//Me salen error desconocido nº 0 ...254
   		 	printf("Error:%s\n",strerror(i));
			
   		 	
		}
	}
	return 0;
}
