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
	
	char* W= "W";
	char* R= "R";

	char buf[256];
	
	mkfifo(W,0777);
	mkfifo(R,0777);

	int fdW = open(W,O_NONBLOCK);
	int fdR = open(R,O_NONBLOCK);

	while(1){
		
		printf("EStoy en el bucle \n");

		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(fdW,&rfds);
		FD_SET(fdR,&rfds);
		
		printf("Estoy haciendo el select \n");
		
		int sel = select(maxi(fdW,fdR)+1,&rfds,NULL,NULL,NULL);
		

		if(sel==-1){	
			printf("El select no devuelve lo que deve \n");
			return -1;
			
		}
		
		printf("Ya he hecho el select \n");
	
		int tubActual;//para el descriptor de fichero de la tuberia actual
		int idActual; //Para saber cual es el identificador de cada una RD = 0 y WD=1
		
		printf("Estoy haciendo las comprobaciones del FD_ISSET \n");
		

		if(FD_ISSET(fdW,&rfds)){
			tubActual =fdW;
			idActual = WR;
		}
		else{
			printf("Error FD_ISSET(fdW,&rfds) \n");
			return -1;
		}

		if(FD_ISSET(fdR,&rfds)){
			tubActual =fdR;
			idActual = RD;
		}
		else{
			printf("Error FD_ISSET(fdR,&rfds) \n");
			return -1;
		}
		
		printf("EStoy empezando a leer \n");

		size_t rc = read(tubActual,buf,255);

		if(rc == -1){
			printf("Hay problemas al realizar la lectura correspondiente de la turbería actual% s\n", buf);

		}
		//Indicando el fin de fichero, por lo que hay que cerrar la tubería y volver a abrirla
		else if(rc == 0){
			close(tubActual);
			read(tubActual,buf,sizeof(char)*255);
		}

		else{
			buf[rc] = '\0';
			printf("Tuberia: %i Datos: %s\n", idActual,buf);
			close(fdW);
			close(fdR);
		}
		
		
	}
	
	

	return 0;
		
}