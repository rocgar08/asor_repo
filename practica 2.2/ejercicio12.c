#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){

	if(argc!=2){
		printf("HAs puesto mal los argumentos \n");
		return -1;	
	}

	int fd = open(argv[1],O_CREAT|O_TRUNC|RDWR,0640);
	if( fd == -1){
		perror("fd");
		return -1;	
	}
	//la salida estándar es 1
	//Redirigir la salida estándar a un fichero
	int fdaux;
	if(fdaux = dup2(fd,1)== -1){
		printf("Error al redirigir a la salida estándar \n");
		return -1;
	}
	else printf("Se ha redirigido a %s\n", argv[1]);
	close(fd);
	return 0;
}