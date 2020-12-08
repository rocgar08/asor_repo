#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, char **argv){

	if(argc!=2){
		printf("HAs puesto mal los argumentos \n");
		return -1;	
	}

	int fd = open(argv[1],O_CREAT|O_TRUNC|O_RDWR,0777);
	if( fd == -1){
		perror("fd");
		return -1;	
	}

	//la salida estándar es 1
	//Escribir un programa que redirija la salida estándar a un fichero
	int fdaux;
	if(fdaux= dup2(fd,2)==-1){
		printf("Error al duplicar el descriptor de fichero a la salida estándar \n");
		return -1;
	}
	else printf("Se ha redirigido a %s\n", argv[1]);

	//Para que se redirija a la salida estandar de error
	if(dup2(fdaux,2)== -1){
		printf("Error al duplicar el descriptor de fichero a la salida de error \n");
		return -1;
	}
	
	else printf("Se ha vuelto a redirigir a %s\n", argv[1]);

	close(fdaux);
	close(fd);
	return 0;
}