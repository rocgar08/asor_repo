#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char **argv){
	/*
	¿En qué casos se imprime la cadena?
       ¿Por qué?  
	Solo con system, ya que con execvp se crea una imagen de 	proceso y sustituye lo que haya debajo de el por el comando que ha sido insertado */
	
	execvp(argv[1],argv +1);
	//system(argv[1] + 1);
	printf("El comando terminó de ejecutarse \n");   
	return 0;
}