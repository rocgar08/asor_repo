#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main( int argc, char **argv){
	
	printf("Estas siendo redirigido al directorio /tmp\n");

	int redir = chdir("/tmp");

	printf("Este es el directorio actual: %s\n",get_current_dir_name());
	        
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


				printf("[H] %i [P] %i\n", getpid(),getppid());
	
				fdOut = open("/tmp/daemon.out",O_CREAT|O_TRUNC|O_RDWR,0777);
				fdIn = open("/tmp/daemon.err",O_CREAT|O_TRUNC|O_RDWR,0777);
				fdE = open("/dev/null",O_CREAT|O_TRUNC,0777);
				
				dup2(fdOut,1);
				dup2(fdIn,0);
				dup2(fdE,2);
				execvp(argv[1],argv +1);


				
		break;
		//yedai
		default: 
			wait(status);
			printf("[P] %i [H] %i \n", getpid(), pid);

		break;
	}

	
	return 0;
}