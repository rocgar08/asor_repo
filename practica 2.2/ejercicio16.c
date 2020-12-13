#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char **argv){
	
	DIR *dir = opendir(argv[1]);
	struct stat info;
	struct dirent *options = readdir(dir);//Devuelve un puntero a la estructura dirent
	ssize_t rl;
	char *aux;

	if(argc!=2){
		printf("You need 2 arguments \n");
		return -1;
	}

	if(stat(argv[1],&info)==-1){
		perror("stat");
		return -1;
	}

	while(options!=NULL){
	    
		aux = malloc(strlen(options->d_name)+ info.st_size + 1);

		switch(info.st_mode & S_IFMT){

		case S_IFREG:  printf("%s \n", options->d_name); break;

		case S_IFDIR:   printf("[/] %s \n", options->d_name); break;

		case S_IFLNK:       

			rl= readlink(argv[1], aux, info.st_size + 1);

			if (rl > info.st_size) {
				fprintf(stderr, "symlink increased in size "
				"between stat() and readlink()\n");
				return -1;
			}
			aux[rl] = '\0';
			printf("[S]: %s->%s \n", options->d_name, info.st_size + 1);
			free(aux);
		break;

		default: printf("[*] %s \n", options->d_name); break;	

		}
	
		options = readdir(dir);//Para salir del bucle
	}

closedir(dir);
return 0;

}