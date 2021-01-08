#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#define RD 0
#define WR 1

int maxi(a,b){ 
	return a>b?a:b;
}

int main(int argc, char **argv){
	
	char buf[256];

	int fdW = open("./tubW",O_RDWR);
	int fdR = open("./tubR",O_RDWR);

	while(1){
		printf("Estoy en el bucle \n");

		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(fdW,&rfds);
		FD_SET(fdR,&rfds);
		
		printf("Estoy haciendo el select \n");
		select(maxi(fdW,fdR)+1,&rfds,NULL,NULL,NULL);

		printf("Ya he hecho el select \n");
	
		int *tubActual;//para el descriptor de fichero de la tuberia actual
		char *idActual; //Para saber cual es el identificador
		
		printf("Estoy haciendo las comprobaciones del FD_ISSET \n");
		
		if(FD_ISSET(fdW,&rfds)){
			tubActual = &fdW;
			idActual = "tubW";
		}
	
		else if(FD_ISSET(fdR,&rfds)){
			tubActual =&fdR;
			idActual = "tubR";
		}
		else{
			printf("Error en el select \n");
			return -1;
		}
		
		printf("Estoy empezando a leer \n");

		size_t rc = read(*tubActual,buf,255);

		if(rc == -1){
			printf("Hay problemas al realizar la lectura correspondiente de la turbería actual% s\n", buf);
			return -1;

		}
		//Indicando el fin de fichero, por lo que hay que cerrar la tubería y volver a abrirla
		else if(rc == 0){
			close(*tubActual);
			*tubActual = open(idActual,O_RDWR); //TAmbién se puede poner el flag RD_ONLY|NON_BLOCK
		}

		else{

			buf[rc] = '\0';
			printf("Tuberia: %i Datos: %s\n", *idActual,buf);
		}
	}
	
	close(fdW);
	close(fdR);
	return 0;
		
}