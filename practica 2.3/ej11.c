/*

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
void esperandoSen(){

	sigset_t cjto;
	sigpending(&cjto);
	if(sigismember(&cjto,SIGINT)==1){
		printf("Capturando señal SIGINT \n");

	}

	if(sigismember(&cjto,SIGTSTP)==1){
		printf("Capturando señal SIGTSTP \n");

	}

}
int main(int argc, char **argv){
	
	//Poner en el terminal export SLEEP_SECS="3"
	sigset_t blk_set;
	sigemptyset(&blk_set);
	sigaddset(&blk_set, SIGINT);
	sigaddset(&blk_set, SIGTSTP);

	char *sleep_sec = getenv("SLEEP_SECS");
	int s = atoi(sleep_sec);
	sleep(s);

	sigprocmask(SIG_BLOCK, &blk_set, NULL);

	esperandoSen();

	sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

	return 0;
}