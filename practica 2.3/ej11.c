/*

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char **argv){
	
	//Poner en el terminal export SLEEP_SECS="3"
	sigset_t blk_set;

	sigemptyset(&blk_set);

	sigaddset(&blk_set, SIGINT);
	sigaddset(&blk_set, SIGTSTP);

	//ACTIVACIÓN DE CERROJO
	sigprocmask(SIG_BLOCK, &blk_set, NULL);
	

	char *sleep_sec = getenv("SLEEP_SECS");
	int s = atoi(sleep_sec);
	sleep(s);
	
	//DESACTIVACIÓN DE CERROJO
	sigprocmask(SIG_UNBLOCK, &blk_set, NULL);
	
	printf("La señal SIGINT ha sido capturada: %i\n", SIGINT);
	printf("La señal SIGTSTP ha sido capturada: %i\n", SIGTSTP);

	return 0;
}