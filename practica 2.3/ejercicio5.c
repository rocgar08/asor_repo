#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char **argv){

	struct rlimit l;
	
	printf("[P] %i [(group: %i) (sesion : %i)] \n", 
	getpid(),getppid(),
	getpgid(getpid()),getsid(getpid()));
	
	char *buf = malloc(sizeof(char)*2048);
	char *currDir = getcwd(buf,sizeof(char)*2048);
	
	printf("Current directory %s\n", currDir);
	//Necesario para obtener el máximo nº de fds
	getrlimit(RLIMIT_NOFILE,&l);
	printf("Max limit %lli\n",l.rlim_max);

	free(buf);
	return 0;
}