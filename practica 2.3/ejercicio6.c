#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

int main( int argc, char **argv){
	/*
	  Crear la sesion y el grupo
	  nuevo proceso para ejecutar la lógica del
	  demonio, la sesión y lo del grupo
	 */
	
	int status;
	pid_t pid = fork();
	
	switch(pid){	
		case -1: 
			printf("Something went wrong \n");
		break;
		//aprendiz de yedai
		case 0:
		setsid();
		int redir = chdir("/tmp");
		printf("Has sido redirigido al directorio tmp \n");
		printf("[H] %i [P] %i [(group: %i) (sesion : %i)] \n", 
			getpid(), getppid(), getpgid(pid), getsid(pid));
		break;
		//yedai
		default: 
			wait(status);
			printf("[P] %i [H] %i [(group: %i) (sesion : %i)] \n", 
				getpid(), pid, getpgid(pid), getsid(pid));
		break;
	}
	return 0;
}