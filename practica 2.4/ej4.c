#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
	//En el terminal hago mkfifo tub
	//al ejecutar el programa le paso el nombre de la tub por el argv[1] y uso un execvp  para escribir en la tuberia./ej4 tub echo "hola" > tub
    //O pasarle por el argv[2]--> ./ej4 tub "Hola como estas"
	//Leer desde el terminal con cat tub
	int fd = open(argv[1],O_WRONLY);
	
	//execvp(argv[2],argv + 1);
	write(fd,argv[2],strlen(argv[2]));
	close(fd);
	return 0;
		
}