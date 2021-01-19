
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>



int main(int argc, char **argv){

	int pipefd[2];
	//Ojo que hay que abrir las tuberias !!!!!!
	pipe(pipefd);
        pid_t pid;


	pid = fork();

		
	switch(pid){
		case -1:
			printf("Error");
			return -1;
		break;
		//El hijo
		case 0: 
			close(pipefd[1]);

			if(dup2(pipefd[0],0)== -1){
				printf("Error dup2(fd[0],) \n");
			}
			close(pipefd[0]);
			//Hay que pasarselo como una lista
			execlp(argv[3],argv[3],argv[4],NULL);
			
		break;
		//El padre
		default:
			close(pipefd[0]);

			if(dup2(pipefd[1],1) == -1){
				printf("Error dup2(fd[1],0) \n");
			}
			close(pipefd[1]);
			execlp(argv[1],argv[1],argv[2],NULL);
		break;
	}
	return 0;
}
