#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//open libraries
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, char **argv){
	
	if(argc!=2){
		printf("Necesitas 2 argumentos\n");
		return -1;
	}
	int fd = open(argv[1],O_CREAT|O_TRUNC|O_RDWR,0666);
	
	if( fd == -1){
		printf("Error al abrir el fichero \n");
		return -1;	
	}
	return 0;
}

