#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv){
	
	int padre_hijo[2];
	int hijo_padre[2];
	
	pipe(padre_hijo);
	pipe(hijo_padre);

	char l[2];
	pid_t pid = fork();
	char buf[256];
	size_t  rc, rc1;

	switch(pid){
		case -1:
			printf("Error");
			return -1;
		break;

		case 0:
			printf("Leyendo en el proceso hijo \n");
       			
			int cont = 0;
			for(cont; cont < 10; cont++){
				rc1 = read(padre_hijo[0],&buf,sizeof(char)*256);
				buf[rc1]='\0';
				printf("Hijo : %s\n",buf);
				sleep(1);
				l[0] = 'l';
				if(cont == 9){
					l[0]='q';

				}
				write(hijo_padre[1],&l,sizeof(char));
			}
		break;
		default:
			
			printf("Leyendo en el proceso padre \n");
			close(hijo_padre[1]);
			close(padre_hijo[0]);
			while(l[0]!='q'){
	       			rc= read(0, &buf, sizeof(char)*256);
				buf[rc]= '\0';
				write(padre_hijo[1],&buf,sizeof(char)*256);
				read(hijo_padre[0] ,&l,sizeof(char));
				l[1] = '\0';
				printf("Caracter %s\n",l);
			}
			close(hijo_padre[0]);
			close(padre_hijo[1]);
	
		break;
	}

	return 0;
}