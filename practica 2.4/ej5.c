#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

int maxi(a,b){ 
	return a>b?a:b;
}

int main(int argc, char **argv){
	

	// En el primer terminal ejecuta  ./ej5
	// En el 2 terminal usas echo > patatas en tubW
	char buf[256];
	//2 tuberias lecturas!!!!!!
	int fdW = open("tubw",O_RDONLY|O_NONBLOCK);
	int fdR = open("tubr",O_RDONLY|O_NONBLOCK);

	do{
		
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(fdW,&rfds);
		FD_SET(fdR,&rfds);
			
		printf("Estoy haciendo el select \n");

		int sel = select(maxi(fdW,fdR)+1,&rfds,NULL,NULL,NULL);
		if(sel == -1){
			printf("Error en sel %s\n",strerror(errno));
			return -1;
		}

		int *tubActual;//para el descriptor de fichero de la tuberia actual
		char *idActual; //Para saber cual es el identificador
		
		if(FD_ISSET(fdW,&rfds)){
			printf("tubw \n");
			tubActual = &fdW;
			idActual = "tubw";
		}
	
		if(FD_ISSET(fdR,&rfds)){
			printf("tubr \n");
			tubActual = &fdR;
			idActual = "tubr";
		}
		
		printf("Estoy empezando a leer \n");
		int rc = read(*tubActual,buf,255);

		if(rc == -1){
			printf("Hay problemas al realizar la lectura correspondiente de la turbería actual% s\n", buf);
			return -1;
		}
		//Indicando el fin de fichero, por lo que hay que cerrar la tubería y volver a abrirla
		else if(rc == 0){
			close(*tubActual);
			*tubActual = open(idActual,O_RDONLY|O_NONBLOCK); //También se puede poner el flag RD_ONLY|NON_BLOCK
		}
		else{
			buf[rc] = '\0';
			printf("Tuberia: %i Datos: %s\n", *idActual,buf);
		}
		
	}while(1);
	
	close(fdW);
	close(fdR);
	return 0;	
}