#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include <signal.h>


#define TRUE 1
#define FALSE 0

volatile int ok = TRUE;

void hand(int state){

	if(state == SIGUSR1) ok = FALSE;
		
}

int main( int argc, char **argv){
	
	
	struct sigaction sa;
	sa.sa_handler = hand;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1,&sa,NULL);

	sleep(atoi(argv[1]));
	
	
	if(ok){
		printf("El ejecutable se va ha  borrar \n");	
		unlink(argv[0]);
		printf("El fichero ha sido borrado \n");
		
	}
	else printf("El fichero no se ha borrado \n");
	
	
	return 0;
}