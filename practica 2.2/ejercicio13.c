#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, char **argv){

	if(argc!=2){
		printf("HAs puesto mal los argumentos \n");
		return -1;	
	}

	int fd = open(argv[1],O_CREAT|O_TRUNC,0640);
	if( fd == -1){
		perror("fd");
		return -1;	
	}

	//la salida estándar es 1
	//Redirija el fd a la salida estándar
	int fdaux = dup2(1,fd);
	printf("Se ha redirigido a %s\n", argv[1]);
	//Para que se redirija a la salida estandar de error
	dup2(fdaux,2);
	printf("Se ha vuelto a redirigir a %s\n", argv[1]);
	return 0;
}