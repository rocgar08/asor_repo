/*Escribir un programa que realice el borrado programado del propio ejecutable. 
El programa tendrá como argumento el número de segundos que esperará antes de borrar el fichero. 
El borrado del fichero se podrá detener si se recibe la señal SIGUSR1.*/

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include <signal.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

volatile int ok = FALSE;

void hand(int state){
	
	if(state == SIGUSR1) ok = TRUE;	
}

int main( int argc, char **argv){
	
	
	struct sigaction sa;
	sa.sa_handler = hand;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1,&sa,NULL);
	
	printf("pid: %i\n",getpid());
	sleep(atoi(argv[1]));
	
	if(!ok){
		printf("El ejecutable se va ha  borrar \n");	
		unlink(argv[0]);
		printf("El fichero ha sido borrado \n");
		
	}
	else printf("El fichero no se ha borrado \n");
	
	return 0;
}