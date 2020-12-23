#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

volatile int cI=0;
volatile int cS =0;

void contar(int state){
	if(state  == SIGINT) cI++;
	if (state == SIGTSTP) cS++;
}

int main(int argc, char **argv){
	
	struct sigaction sa;
	sa.sa_handler = contar;
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT,&sa,NULL);
	sigaction(SIGTSTP,&sa,NULL);

	while( cI+cS < 10){
		
	};

	printf("La señal SIGINT ha sido capturada %i\n", cI);
	printf("La señal SIGTSTP ha sido capturada %i\n",cS);
	return 0;
}