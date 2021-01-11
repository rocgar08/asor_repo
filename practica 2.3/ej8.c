#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main( int argc, char **argv){
	
	printf("Estás siendo redirigido al directorio /tmp\n");

	int redir = chdir("/tmp");
	        
	if(redir == -1){
		printf("No has sido redirigido al directorio tmp\n");
		return -1;
	}

	pid_t pid = fork();
	int status,fdOut,fdIn,fdE;
	
	
	switch(pid){	
		case -1: 
			printf("Something went wrong \n");
		break;
		//aprendiz de yedai
		case 0:
				printf("[H] %i [P] %i [(group: %i) (sesion : %i)] \n", getpid(),
				        getppid(), getpgid(pid), getsid(getpid()));
				/*
				La salida estándar al fichero /tmp/daemon.out.
				La salida de error estándar al fichero /tmp/daemon.err.
				La entrada estándar a /dev/null.
				*/
				fdOut = open("/tmp/daemon.out",O_CREAT|O_TRUNC,0777);
				fdIn = open("/dev/null/",O_CREAT|O_TRUNC,0777);
				fdE = open("tmp/daemon.err",O_CREAT|O_TRUNC,0777);
				
				dup2(fdOut,1);
				dup2(fdIn,0);
				dup2(fdE,2);
				execvp(argv[1],argv +1);
				
				
		break;
		//yedai
		default: 
			wait(status);
			printf("[P] %i [H] %i [(group: %i) (sesion : %i)] \n", 
				getpid(), pid, getpgid(pid), getsid(getpid()));
		break;
	}

	
	return 0;
}